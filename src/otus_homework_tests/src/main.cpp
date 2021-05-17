#define CATCH_CONFIG_MAIN
#include <fakeit.hpp>
#include <catch2/catch.hpp>

#include <otus_homework/interfaces/i_movable.hpp>
#include <otus_homework/interfaces/i_rotatable.hpp>
#include <otus_homework/commands/move_command.hpp>
#include <otus_homework/commands/rotate_command.hpp>

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

TEST_CASE("i_rotatable rotating test")
{
	int direction(3);

	Mock<i_rotatable> i_rotatable_mock;
	When(Method(i_rotatable_mock, get_direction)).AlwaysDo([&]() { return direction; });
	When(Method(i_rotatable_mock, get_angular_velocity)).AlwaysReturn(14);
	When(Method(i_rotatable_mock, get_max_directions)).AlwaysReturn(16);
	When(Method(i_rotatable_mock, set_direction)).AlwaysDo([&](const int new_direction)
		{
			direction = new_direction;
		}
	);

	auto pointer_to_rotatable = std::shared_ptr<i_rotatable>(&i_rotatable_mock(), [](...)
		{
		});

	rotate_command cmd(pointer_to_rotatable);
	cmd.execute();

	REQUIRE(pointer_to_rotatable->get_direction() == 1);
}

TEST_CASE("i_rotatable direction getting is not available test")
{
	Mock<i_rotatable> i_rotatable_mock;
	When(Method(i_rotatable_mock, get_direction)).AlwaysThrow(std::runtime_error("Direction is not available"));
	When(Method(i_rotatable_mock, get_angular_velocity)).AlwaysReturn(0);
	When(Method(i_rotatable_mock, get_max_directions)).AlwaysReturn(0);

	const auto pointer_to_rotatable = std::shared_ptr<i_rotatable>(&i_rotatable_mock(), [](...)
	{
	});
	
	rotate_command cmd(pointer_to_rotatable);

	REQUIRE_THROWS_WITH(cmd.execute(), "Direction is not available");	
}

TEST_CASE("i_rotatable angular velocity getting is not available test")
{
	Mock<i_rotatable> i_rotatable_mock;
	When(Method(i_rotatable_mock, get_direction)).AlwaysReturn(0);
	When(Method(i_rotatable_mock, get_angular_velocity)).AlwaysThrow(std::runtime_error("Angular velocity is not available"));
	When(Method(i_rotatable_mock, get_max_directions)).AlwaysReturn(0);

	const auto pointer_to_rotatable = std::shared_ptr<i_rotatable>(&i_rotatable_mock(), [](...)
		{
		});

	rotate_command cmd(pointer_to_rotatable);

	REQUIRE_THROWS_WITH(cmd.execute(), "Angular velocity is not available");
}

TEST_CASE("i_rotatable max directions getting is not available test")
{
	Mock<i_rotatable> i_rotatable_mock;
	When(Method(i_rotatable_mock, get_direction)).AlwaysReturn(0);
	When(Method(i_rotatable_mock, get_angular_velocity)).AlwaysReturn(0);
	When(Method(i_rotatable_mock, get_max_directions)).AlwaysThrow(std::runtime_error("Max directions is not available"));

	const auto pointer_to_rotatable = std::shared_ptr<i_rotatable>(&i_rotatable_mock(), [](...)
		{
		});

	rotate_command cmd(pointer_to_rotatable);

	REQUIRE_THROWS_WITH(cmd.execute(), "Max directions is not available");
}

TEST_CASE("i_rotatable direction setting is not available test")
{
	Mock<i_rotatable> i_rotatable_mock;
	When(Method(i_rotatable_mock, get_direction)).AlwaysReturn(0);
	When(Method(i_rotatable_mock, get_angular_velocity)).AlwaysReturn(0);
	When(Method(i_rotatable_mock, get_max_directions)).AlwaysReturn(1);
	When(Method(i_rotatable_mock, set_direction)).AlwaysDo([&](const int new_direction)
		{
			throw std::runtime_error("Direction setting is not available");
		}
	);

	const auto pointer_to_rotatable = std::shared_ptr<i_rotatable>(&i_rotatable_mock(), [](...)
	{
	});

	rotate_command cmd(pointer_to_rotatable);
	
	REQUIRE_THROWS_WITH(cmd.execute(), "Direction setting is not available");
}