#include <catch2/catch.hpp>
#include <fakeit.hpp>

#include <otus_homework/interfaces/i_fuel_burnable.hpp>
#include <otus_homework/interfaces/i_fuel_checkable.hpp>
#include <otus_homework/interfaces/i_velocity_changable.hpp>
#include <otus_homework/interfaces/i_rotatable.hpp>
#include <otus_homework/commands/burn_fuel_command.hpp>
#include <otus_homework/commands/check_fuel_command.hpp>
#include <otus_homework/commands/rotate_command.hpp>
#include <otus_homework/commands/move_command.hpp>
#include <otus_homework/commands/change_velocity_command.hpp>
#include <otus_homework/commands/macro_command.hpp>

using namespace fakeit;
using namespace tank_battle_server;

const auto pi = 3.1415926535897932384626433832795;

TEST_CASE("i_fuel_checkable check running out fuel test")
{
	Mock<i_fuel_checkable> i_fuel_checkable_mock;
	When(Method(i_fuel_checkable_mock, get_fuel_amount)).AlwaysDo([&]() { return 1; });
	When(Method(i_fuel_checkable_mock, get_fuel_burn_velocity)).AlwaysReturn(2);

	const auto pointer_to_fuel_checkable = std::shared_ptr<i_fuel_checkable>(&i_fuel_checkable_mock(), [](...)
	{
	});

	check_fuel_command cmd(pointer_to_fuel_checkable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_fuel_checkable check fuel test")
{
	Mock<i_fuel_checkable> i_fuel_checkable_mock;
	When(Method(i_fuel_checkable_mock, get_fuel_amount)).AlwaysDo([&]() { return 2; });
	When(Method(i_fuel_checkable_mock, get_fuel_burn_velocity)).AlwaysReturn(1);

	const auto pointer_to_fuel_checkable = std::shared_ptr<i_fuel_checkable>(&i_fuel_checkable_mock(), [](...)
	{
	});

	check_fuel_command cmd(pointer_to_fuel_checkable);

	REQUIRE_NOTHROW(cmd.execute());
}

TEST_CASE("i_fuel_checkable fuel amount getting is not available test")
{
	Mock<i_fuel_checkable> i_fuel_checkable_mock;
	When(Method(i_fuel_checkable_mock, get_fuel_amount)).AlwaysThrow(std::runtime_error("fuel amount getting is not available"));
	When(Method(i_fuel_checkable_mock, get_fuel_burn_velocity)).AlwaysReturn(1);

	const auto pointer_to_fuel_checkable = std::shared_ptr<i_fuel_checkable>(&i_fuel_checkable_mock(), [](...)
	{
	});

	check_fuel_command cmd(pointer_to_fuel_checkable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_fuel_checkable fuel burn velocity getting is not available test")
{
	Mock<i_fuel_checkable> i_fuel_checkable_mock;
	When(Method(i_fuel_checkable_mock, get_fuel_amount)).AlwaysReturn(1);
	When(Method(i_fuel_checkable_mock, get_fuel_burn_velocity)).AlwaysThrow(std::runtime_error("fuel burn velocity getting is not available"));

	const auto pointer_to_fuel_checkable = std::shared_ptr<i_fuel_checkable>(&i_fuel_checkable_mock(), [](...)
	{
	});

	check_fuel_command cmd(pointer_to_fuel_checkable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_fuel_burnable burn running out fuel test")
{
	auto fuel_amount = 1;

	Mock<i_fuel_burnable> i_fuel_burnable_mock;
	When(Method(i_fuel_burnable_mock, get_fuel_amount)).AlwaysDo([&]() { return fuel_amount; });
	When(Method(i_fuel_burnable_mock, get_fuel_burn_velocity)).AlwaysReturn(2);
	When(Method(i_fuel_burnable_mock, set_fuel_amount)).AlwaysDo([&](const int amount)
		{
			fuel_amount = amount;
		}
	);

	const auto pointer_to_fuel_burnable = std::shared_ptr<i_fuel_burnable>(&i_fuel_burnable_mock(), [](...)
	{
	});

	burn_fuel_command cmd(pointer_to_fuel_burnable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_fuel_burnable burn fuel test")
{
	auto fuel_amount = 2;

	Mock<i_fuel_burnable> i_fuel_burnable_mock;
	When(Method(i_fuel_burnable_mock, get_fuel_amount)).AlwaysDo([&]() { return fuel_amount; });
	When(Method(i_fuel_burnable_mock, get_fuel_burn_velocity)).AlwaysReturn(1);
	When(Method(i_fuel_burnable_mock, set_fuel_amount)).AlwaysDo([&](const int amount)
		{
			fuel_amount = amount;
		}
	);

	const auto pointer_to_fuel_burnable = std::shared_ptr<i_fuel_burnable>(&i_fuel_burnable_mock(), [](...)
	{
	});

	burn_fuel_command cmd(pointer_to_fuel_burnable);
	cmd.execute();

	REQUIRE(fuel_amount == 1);
}

TEST_CASE("i_fuel_burnable fuel amount getting is not available test")
{
	Mock<i_fuel_burnable> i_fuel_burnable_mock;
	When(Method(i_fuel_burnable_mock, get_fuel_amount)).AlwaysThrow(std::runtime_error("fuel amount getting is not available"));
	When(Method(i_fuel_burnable_mock, get_fuel_burn_velocity)).AlwaysReturn(1);
	When(Method(i_fuel_burnable_mock, set_fuel_amount)).AlwaysDo([&](const int amount)
	{
	});

	const auto pointer_to_fuel_burnable = std::shared_ptr<i_fuel_burnable>(&i_fuel_burnable_mock(), [](...)
	{
	});

	burn_fuel_command cmd(pointer_to_fuel_burnable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_fuel_burnable fuel burn velocity getting is not available test")
{
	Mock<i_fuel_burnable> i_fuel_burnable_mock;
	When(Method(i_fuel_burnable_mock, get_fuel_amount)).AlwaysReturn(1);
	When(Method(i_fuel_burnable_mock, get_fuel_burn_velocity)).AlwaysThrow(std::runtime_error("fuel burn velocity getting is not available"));
	When(Method(i_fuel_burnable_mock, set_fuel_amount)).AlwaysDo([&](const int amount)
	{
	});

	const auto pointer_to_fuel_burnable = std::shared_ptr<i_fuel_burnable>(&i_fuel_burnable_mock(), [](...)
	{
	});

	burn_fuel_command cmd(pointer_to_fuel_burnable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_fuel_burnable fuel amount setting is not available test")
{
	Mock<i_fuel_burnable> i_fuel_burnable_mock;
	When(Method(i_fuel_burnable_mock, get_fuel_amount)).AlwaysReturn(1);
	When(Method(i_fuel_burnable_mock, get_fuel_burn_velocity)).AlwaysReturn(1);
	When(Method(i_fuel_burnable_mock, set_fuel_amount)).AlwaysDo([&](const int amount)
		{
			throw std::runtime_error("fuel amount setting is not available");
		}
	);

	const auto pointer_to_fuel_burnable = std::shared_ptr<i_fuel_burnable>(&i_fuel_burnable_mock(), [](...)
	{
	});

	burn_fuel_command cmd(pointer_to_fuel_burnable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("simple macro_command test")
{
	auto counter{0};

	Mock<i_command> i_increase_counter_command_mock;
	When(Method(i_increase_counter_command_mock, execute)).AlwaysDo([&]()
		{
			++counter;
		}
	);

	Mock<i_command> i_throwable_command_mock;
	When(Method(i_throwable_command_mock, execute)).AlwaysThrow(std::runtime_error("throw from throwable command"));

	const auto pointer_to_increase_counter_command = std::shared_ptr<i_command>(&i_increase_counter_command_mock(), [](...)
	{
	});

	const auto pointer_to_throwable_command = std::shared_ptr<i_command>(&i_throwable_command_mock(), [](...)
	{
	});

	std::list<std::shared_ptr<i_command>> commands{
		pointer_to_increase_counter_command,
		pointer_to_throwable_command,
		pointer_to_increase_counter_command
	};

	macro_command simple_macro_command(commands);

	REQUIRE_THROWS_WITH(simple_macro_command.execute(), "command exception");
	REQUIRE(counter == 1);
}


TEST_CASE("move with fuel burning command test")
{
	auto fuel_amount = 2;
	const auto fuel_burn_velocity = 1;
	movement_vector position({12, 5});
	movement_vector velocity({-7, 3});

	Mock<i_fuel_checkable> i_fuel_checkable_mock;
	Mock<i_movable> i_movable_mock;
	Mock<i_fuel_burnable> i_fuel_burnable_mock;

	When(Method(i_fuel_checkable_mock, get_fuel_amount)).AlwaysDo([&]() { return fuel_amount; });
	When(Method(i_fuel_checkable_mock, get_fuel_burn_velocity)).AlwaysDo([&]() { return fuel_burn_velocity; });
	When(Method(i_movable_mock, get_position)).AlwaysDo([&]() { return position; });
	When(Method(i_movable_mock, get_velocity)).AlwaysDo([&]() { return velocity; });
	When(Method(i_movable_mock, set_position)).AlwaysDo([&](movement_vector const& new_position)
		{
			position = new_position;
		}
	);
	When(Method(i_fuel_burnable_mock, get_fuel_amount)).AlwaysDo([&]() { return fuel_amount; });
	When(Method(i_fuel_burnable_mock, get_fuel_burn_velocity)).AlwaysDo([&]() { return fuel_burn_velocity; });
	When(Method(i_fuel_burnable_mock, set_fuel_amount)).AlwaysDo([&](const int amount)
		{
			fuel_amount = amount;
		}
	);

	const auto pointer_to_fuel_checkable = std::shared_ptr<i_fuel_checkable>(&i_fuel_checkable_mock(), [](...)
	{
	});
	const auto pointer_to_fuel_burnable = std::shared_ptr<i_fuel_burnable>(&i_fuel_burnable_mock(), [](...)
	{
	});
	auto pointer_to_movable = std::shared_ptr<i_movable>(&i_movable_mock(), [](...)
	{
	});

	const auto check_fuel_cmd = std::make_shared<check_fuel_command>(pointer_to_fuel_checkable);
	const auto move_cmd = std::make_shared<move_command>(pointer_to_movable);
	const auto burn_fuel_cmd = std::make_shared<burn_fuel_command>(pointer_to_fuel_burnable);

	std::list<std::shared_ptr<i_command>> commands{
		check_fuel_cmd,
		move_cmd,
		burn_fuel_cmd
	};

	macro_command move_with_fuel_burn_command(commands);

	REQUIRE_NOTHROW(move_with_fuel_burn_command.execute());
	REQUIRE(fuel_amount == 1);
	REQUIRE(position == movement_vector({5, 8}));
	REQUIRE_NOTHROW(move_with_fuel_burn_command.execute());
	REQUIRE(fuel_amount == 0);
	REQUIRE(position == movement_vector({-2, 11}));
	REQUIRE_THROWS_WITH(move_with_fuel_burn_command.execute(), "command exception");
}

TEST_CASE("i_velocity_changable change velocity test")
{
	movement_vector velocity({1, 0});
	movement_vector velocity_change_shift({1, 0});
	const auto velocity_change_angle(pi / 2.);

	Mock<i_velocity_changable> i_velocity_changable_mock;

	When(Method(i_velocity_changable_mock, get_velocity)).AlwaysDo([&]() { return velocity; });
	When(Method(i_velocity_changable_mock, get_velocity_change_shift)).AlwaysDo([&]() { return velocity_change_shift; });
	When(Method(i_velocity_changable_mock, get_velocity_change_angle)).AlwaysDo([&]() { return velocity_change_angle; });
	When(Method(i_velocity_changable_mock, set_velocity)).AlwaysDo([&](movement_vector const& new_velocity)
		{
			velocity = new_velocity;
		}
	);

	const auto pointer_to_velocity_changable = std::shared_ptr<i_velocity_changable>(&i_velocity_changable_mock(), [](...)
	{
	});

	change_velocity_command cmd(pointer_to_velocity_changable);
	cmd.execute();

	REQUIRE(velocity == movement_vector({0, 2}));
}

TEST_CASE("i_velocity_changable velocity getting is not available test")
{
	movement_vector velocity({-7, 3});
	movement_vector velocity_change_shift({12, 5});
	const auto velocity_change_angle(pi / 2);

	Mock<i_velocity_changable> i_velocity_changable_mock;

	When(Method(i_velocity_changable_mock, get_velocity)).AlwaysThrow(std::runtime_error("velocity getting is not available"));
	When(Method(i_velocity_changable_mock, get_velocity_change_shift)).AlwaysDo([&]() { return velocity_change_shift; });
	When(Method(i_velocity_changable_mock, get_velocity_change_angle)).AlwaysDo([&]() { return velocity_change_angle; });
	When(Method(i_velocity_changable_mock, set_velocity)).AlwaysDo([&](movement_vector const& new_velocity)
		{
			velocity = new_velocity;
		}
	);

	const auto pointer_to_velocity_changable = std::shared_ptr<i_velocity_changable>(&i_velocity_changable_mock(), [](...)
	{
	});

	change_velocity_command cmd(pointer_to_velocity_changable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_velocity_changable velocity change shift getting is not available test")
{
	movement_vector velocity({-7, 3});
	movement_vector velocity_change_shift({12, 5});

	Mock<i_velocity_changable> i_velocity_changable_mock;

	When(Method(i_velocity_changable_mock, get_velocity)).AlwaysDo([&]() { return velocity; });
	When(Method(i_velocity_changable_mock, get_velocity_change_shift)).AlwaysDo([&]() { return velocity_change_shift; });
	When(Method(i_velocity_changable_mock, get_velocity_change_angle)).AlwaysThrow(std::runtime_error("velocity change angle getting is not available"));
	When(Method(i_velocity_changable_mock, set_velocity)).AlwaysDo([&](movement_vector const& new_velocity)
		{
			velocity = new_velocity;
		}
	);

	const auto pointer_to_velocity_changable = std::shared_ptr<i_velocity_changable>(&i_velocity_changable_mock(), [](...)
	{
	});

	change_velocity_command cmd(pointer_to_velocity_changable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_velocity_changable velocity change angle getting is not available test")
{
	movement_vector velocity({-7, 3});
	const auto velocity_change_angle(pi / 2);

	Mock<i_velocity_changable> i_velocity_changable_mock;

	When(Method(i_velocity_changable_mock, get_velocity)).AlwaysDo([&]() { return velocity; });
	When(Method(i_velocity_changable_mock, get_velocity_change_shift)).AlwaysThrow(std::runtime_error("velocity change getting is not available"));
	When(Method(i_velocity_changable_mock, get_velocity_change_angle)).AlwaysDo([&]() { return velocity_change_angle; });
	When(Method(i_velocity_changable_mock, set_velocity)).AlwaysDo([&](movement_vector const& new_velocity)
		{
			velocity = new_velocity;
		}
	);

	const auto pointer_to_velocity_changable = std::shared_ptr<i_velocity_changable>(&i_velocity_changable_mock(), [](...)
	{
	});

	change_velocity_command cmd(pointer_to_velocity_changable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("i_velocity_changable velocity setting is not available test")
{
	movement_vector velocity({-7, 3});
	movement_vector velocity_change({12, 5});
	const auto velocity_change_angle(pi / 2);

	Mock<i_velocity_changable> i_velocity_changable_mock;

	When(Method(i_velocity_changable_mock, get_velocity)).AlwaysDo([&]() { return velocity; });
	When(Method(i_velocity_changable_mock, get_velocity_change_shift)).AlwaysDo([&]() { return velocity_change; });
	When(Method(i_velocity_changable_mock, get_velocity_change_angle)).AlwaysDo([&]() { return velocity_change_angle; });
	When(Method(i_velocity_changable_mock, set_velocity)).AlwaysDo([&](movement_vector const& new_velocity)
		{
			throw std::runtime_error("velocity setting is not available");
		}
	);

	const auto pointer_to_velocity_changable = std::shared_ptr<i_velocity_changable>(&i_velocity_changable_mock(), [](...)
	{
	});

	change_velocity_command cmd(pointer_to_velocity_changable);

	REQUIRE_THROWS_WITH(cmd.execute(), "command exception");
}

TEST_CASE("rotating with velocity changing command test")
{
	movement_vector position({0, 0});
	movement_vector velocity({1, 0});
	movement_vector velocity_change_shift({1, 0});

	auto direction(0);
	const auto prev_direction = direction;
	const auto angular_velocity(4);
	const auto max_directions(16);

	Mock<i_rotatable> i_rotatable_mock;
	Mock<i_velocity_changable> i_velocity_changable_mock;
	Mock<i_movable> i_movable_mock;

	When(Method(i_rotatable_mock, get_direction)).AlwaysDo([&]() { return direction; });
	When(Method(i_rotatable_mock, get_angular_velocity)).AlwaysReturn(angular_velocity);
	When(Method(i_rotatable_mock, get_max_directions)).AlwaysReturn(max_directions);
	When(Method(i_rotatable_mock, set_direction)).AlwaysDo([&](const int new_direction){ direction = new_direction; });
	
	When(Method(i_velocity_changable_mock, get_velocity)).AlwaysDo([&]() { return velocity; });
	When(Method(i_velocity_changable_mock, get_velocity_change_shift)).AlwaysDo([&](){ return velocity_change_shift; });
	When(Method(i_velocity_changable_mock, get_velocity_change_angle)).AlwaysDo([&]() { return 2 * pi / max_directions * (fabs(direction - prev_direction)); });
	When(Method(i_velocity_changable_mock, set_velocity)).AlwaysDo([&](movement_vector const& new_velocity)
		{
			velocity = new_velocity;
		}
	);
	
	When(Method(i_movable_mock, get_position)).AlwaysDo([&]() { return position; });
	When(Method(i_movable_mock, get_velocity)).AlwaysDo([&]() { return velocity; });
	When(Method(i_movable_mock, set_position)).AlwaysDo([&](movement_vector const& new_position)
		{
			position = new_position;
		}
	);

	const auto pointer_to_rotatable = std::shared_ptr<i_rotatable>(&i_rotatable_mock(), [](...)
	{
	});
	const auto pointer_to_velocity_changable = std::shared_ptr<i_velocity_changable>(&i_velocity_changable_mock(), [](...)
	{
	});
	auto pointer_to_movable = std::shared_ptr<i_movable>(&i_movable_mock(), [](...)
	{
	});

	const auto rotate_cmd = std::make_shared<rotate_command>(pointer_to_rotatable);
	const auto change_velocity_cmd = std::make_shared<change_velocity_command>(pointer_to_velocity_changable);
	const auto move_cmd = std::make_shared<move_command>(pointer_to_movable);

	std::list<std::shared_ptr<i_command>> commands{
		rotate_cmd,
		change_velocity_cmd,
		move_cmd
	};

	macro_command rotate_with_movement_vector_change_command(commands);

	REQUIRE_NOTHROW(rotate_with_movement_vector_change_command.execute());
	REQUIRE(direction == 4);
	REQUIRE(velocity == movement_vector({ 0, 2 }));
	REQUIRE(position == movement_vector({ 0, 2 }));
}
