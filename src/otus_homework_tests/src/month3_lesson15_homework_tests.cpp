#include <catch2/catch.hpp>
#include <fakeit.hpp>

#include <otus_homework/adapters/generated/movable_adapter.hpp>

using namespace fakeit;
using namespace tank_battle_server;

TEST_CASE("generated movable_adapter exists test")
{
	auto position = movement_vector({0, 0});

	Mock<i_uobject> i_uobject_mock;
	When(Method(i_uobject_mock, get_value)).AlwaysDo(
		[&](std::string const& key) { return position; }
	);
	When(Method(i_uobject_mock, set_value)).AlwaysDo([&](std::string const& key, std::any const& value)
	{
		position = std::any_cast<movement_vector>(value);
	});

	const auto pointer_to_uobject = std::shared_ptr<i_uobject>(&i_uobject_mock(), [](...)
	{
	});

	movable_adapter adapter(pointer_to_uobject);

	REQUIRE(adapter.get_position() == movement_vector({ 0,0 }));
	adapter.set_position(movement_vector({1, 1}));
	REQUIRE(adapter.get_position() == movement_vector({1, 1}));
}