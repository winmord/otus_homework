#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <thread>

#include <otus_homework/utils/ioc_container.hpp>
#include <otus_homework/commands/move_command.hpp>
#include <otus_homework/globals.hpp>

using namespace fakeit;
using namespace tank_battle_server;


TEST_CASE("ioc_container dependency register test")
{
	movement_vector position({12, 5});

	Mock<i_movable> i_movable_mock;
	When(Method(i_movable_mock, get_position)).AlwaysDo([&]() { return position; });
	When(Method(i_movable_mock, get_velocity)).AlwaysReturn(movement_vector({-7, 3}));
	When(Method(i_movable_mock, set_position)).AlwaysDo([&](movement_vector const& new_position)
		{
			position = new_position;
		}
	);

	auto pointer_to_movable = std::shared_ptr<i_movable>(&i_movable_mock(), [](...)
	{
	});

	const auto move_lambda = std::function<std::shared_ptr<i_command>(std::shared_ptr<i_movable>)>(
		[](std::shared_ptr<i_movable> const& movable)
		{
			return std::make_shared<move_command>(movable);
		}
	);

	ioc_provider::IoC.resolve<i_command>(std::string("ioc.register"), std::string("go straight"), move_lambda)->execute();
	ioc_provider::IoC.resolve<i_command>(std::string("go straight"), pointer_to_movable)->execute();

	REQUIRE(pointer_to_movable->get_position() == movement_vector({ 5, 8 }));

	const auto int_lambda = std::function<std::shared_ptr<int>()>(
		[]()
		{
			return std::make_shared<int>(1);
		}
	);
	ioc_provider::IoC.resolve<i_command>(std::string("ioc.register"), std::string("int_dependency"), int_lambda)->execute();
	REQUIRE(*ioc_provider::IoC.resolve<int>(std::string("int_dependency")) == 1);
}

TEST_CASE("ioc_container dependency unregister test")
{
	const auto int_lambda = std::function<std::shared_ptr<int>()>(
		[]()
		{
			return std::make_shared<int>(1);
		}
	);
	ioc_provider::IoC.resolve<i_command>(std::string("ioc.register"), std::string("int_dependency"), int_lambda)->execute();
	REQUIRE(*ioc_provider::IoC.resolve<int>("int_dependency") == 1);

	ioc_provider::IoC.resolve<i_command>(std::string("ioc.unregister"), std::string("int_dependency"))->execute();
	REQUIRE_THROWS(ioc_provider::IoC.resolve<int>(std::string("int_dependency")));
}

TEST_CASE("ioc_container scopes test")
{
	const auto int_lambda = std::function<std::shared_ptr<int>()>(
		[]()
		{
			return std::make_shared<int>(1);
		}
	);
	ioc_provider::IoC.resolve<i_command>(std::string("ioc.register"), std::string("int_dependency"), int_lambda)->execute();
	REQUIRE(*ioc_provider::IoC.resolve<int>(std::string("int_dependency")) == 1);
	
	auto other_scope_thread = std::thread([&]()
		{
			REQUIRE_THROWS(ioc_provider::IoC.resolve<int>(std::string("int_dependency")));
		}
	);

	other_scope_thread.join();

	REQUIRE(*ioc_provider::IoC.resolve<int>(std::string("int_dependency")) == 1);

	ioc_provider::IoC.resolve<i_command>(std::string("scopes.new"), std::string("new_test_scope"))->execute();

	REQUIRE_THROWS(ioc_provider::IoC.resolve<i_command>(std::string("scopes.current"), std::string("unexist_scope"))->execute());
	
	ioc_provider::IoC.resolve<i_command>(std::string("scopes.current"), std::string("new_test_scope"))->execute();
	REQUIRE_THROWS(*ioc_provider::IoC.resolve<int>(std::string("int_dependency")) == 1);
}