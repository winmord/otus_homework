#define CATCH_CONFIG_MAIN
#include <fakeit.hpp>
#include <catch2/catch.hpp>

#include <otus_homework/interfaces/i_movable.hpp>
#include <otus_homework/commands/move_command.hpp>

using namespace fakeit;
using namespace tank_battle_server;

TEST_CASE("i_movable moving test")
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
	
	move_command cmd(pointer_to_movable);
	cmd.execute();

	REQUIRE(pointer_to_movable->get_position() == movement_vector({5, 8}));
}

TEST_CASE("i_movable position getting is not available test")
{
	Mock<i_movable> i_movable_mock;
	When(Method(i_movable_mock, get_position)).AlwaysThrow(std::runtime_error("Position is not available"));
	When(Method(i_movable_mock, get_velocity)).AlwaysReturn(movement_vector({0, 0}));

	const auto pointer_to_movable = std::shared_ptr<i_movable>(&i_movable_mock(), [](...)
	{
	});
	
	move_command cmd(pointer_to_movable);

	REQUIRE_THROWS_WITH(cmd.execute(), "Position is not available");
}

TEST_CASE("i_movable velocity getting is not available test")
{
	Mock<i_movable> i_movable_mock;
	When(Method(i_movable_mock, get_position)).AlwaysReturn(movement_vector({0, 0}));
	When(Method(i_movable_mock, get_velocity)).AlwaysThrow(std::runtime_error("Velocity is not available"));

	const auto pointer_to_movable = std::shared_ptr<i_movable>(&i_movable_mock(), [](...)
	{
	});
	
	move_command cmd(pointer_to_movable);

	REQUIRE_THROWS_WITH(cmd.execute(), "Velocity is not available");
}

TEST_CASE("i_movable position setting is not available test")
{
	Mock<i_movable> i_movable_mock;
	When(Method(i_movable_mock, get_position)).AlwaysReturn(movement_vector({ 0, 0 }));
	When(Method(i_movable_mock, get_velocity)).AlwaysReturn(movement_vector({ 0, 0 }));
	When(Method(i_movable_mock, set_position)).AlwaysDo([&](movement_vector const& new_position)
		{
			throw std::runtime_error("Position setting is not available");
		}
	);

	const auto pointer_to_movable = std::shared_ptr<i_movable>(&i_movable_mock(), [](...)
	{
	});

	move_command cmd(pointer_to_movable);
	
	REQUIRE_THROWS_WITH(cmd.execute(), "Position setting is not available");
}