#include <catch2/catch.hpp>
#include <fakeit.hpp>

#include <mutex>
#include <condition_variable>

#include <otus_homework/commands/hard_stop_command.hpp>
#include <otus_homework/commands/soft_stop_command.hpp>
#include <otus_homework/blocking_queue.hpp>
#include <otus_homework/command_executor.hpp>

using namespace fakeit;
using namespace tank_battle_server;

TEST_CASE("command_executor is running test")
{
	auto is_executed{false};
	std::condition_variable execution_condition;

	Mock<i_command> i_command_mock;
	When(Method(i_command_mock, execute)).AlwaysDo([&]()
		{
			is_executed = true;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			execution_condition.notify_one();
		}
	);

	auto command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();

	const auto pointer_to_command = std::shared_ptr<i_command>(&i_command_mock(), [](...)
	{
	});

	command_queue->push(pointer_to_command);

	command_executor cmd_executor(command_queue);

	const auto hard_stop = std::make_shared<hard_stop_command>();
	command_queue->push(hard_stop);

	std::mutex m;
	std::unique_lock<std::mutex> locker(m);

	execution_condition.wait_for(locker, std::chrono::milliseconds(1000), [&]()
	                             {
		                             return is_executed;
	                             }
	);

	REQUIRE(is_executed);
}

void check_command_executor_finish(command_executor const& cmd_executor)
{
	auto executor_is_started{true};
	std::condition_variable executor_finish_condition;

	auto executor_finish_checker = std::thread([&]()
		{
			while (executor_is_started)
			{
				executor_is_started = cmd_executor.is_started();
				if (!executor_is_started) executor_finish_condition.notify_one();
			}
		}
	);

	std::mutex m;
	std::unique_lock<std::mutex> locker(m);

	executor_finish_condition.wait(locker, [&]()
	                               {
		                               return !executor_is_started;
	                               }
	);

	if (executor_finish_checker.joinable()) executor_finish_checker.join();
}

TEST_CASE("command_executor hard_stop test")
{
	Mock<i_command> i_command_mock;
	When(Method(i_command_mock, execute)).AlwaysDo([&]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	);

	const auto commands_count = 2;
	auto command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();

	const auto pointer_to_command = std::shared_ptr<i_command>(&i_command_mock(), [](...)
	{
	});

	for (auto command_number = 0; command_number < commands_count; command_number++)
	{
		command_queue->push(pointer_to_command);
	}

	command_executor cmd_executor(command_queue);

	const auto hard_stop = std::make_shared<hard_stop_command>();
	command_queue->push(hard_stop);
	command_queue->push(pointer_to_command);

	check_command_executor_finish(cmd_executor);

	REQUIRE_FALSE(cmd_executor.is_started());
	REQUIRE_FALSE(command_queue->empty());
}

TEST_CASE("command_executor soft_stop test")
{
	Mock<i_command> i_command_mock;
	When(Method(i_command_mock, execute)).AlwaysDo([&]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	);

	const auto commands_count = 2;
	auto command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();

	const auto pointer_to_command = std::shared_ptr<i_command>(&i_command_mock(), [](...)
	{
	});

	for (auto command_number = 0; command_number < commands_count; command_number++)
	{
		command_queue->push(pointer_to_command);
	}

	const command_executor cmd_executor(command_queue);

	const auto soft_stop = std::make_shared<soft_stop_command>();
	command_queue->push(soft_stop);
	command_queue->push(pointer_to_command);

	check_command_executor_finish(cmd_executor);

	REQUIRE_FALSE(cmd_executor.is_started());
	REQUIRE(command_queue->empty());
}

TEST_CASE("command_executor soft_stop by timeout test")
{
	Mock<i_command> i_command_mock;
	When(Method(i_command_mock, execute)).AlwaysDo([&]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	);

	const auto commands_count = 2;
	auto command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();

	const auto pointer_to_command = std::shared_ptr<i_command>(&i_command_mock(), [](...)
	{
	});

	for (auto command_number = 0; command_number < commands_count; command_number++)
	{
		command_queue->push(pointer_to_command);
	}

	const command_executor cmd_executor(command_queue);

	const auto soft_stop = std::make_shared<soft_stop_command>();
	command_queue->push(soft_stop);
	command_queue->push(pointer_to_command);
	for (auto command_number = 0; command_number < commands_count + 10; command_number++)
	{
		command_queue->push(pointer_to_command);
	}

	check_command_executor_finish(cmd_executor);

	REQUIRE_FALSE(cmd_executor.is_started());
	REQUIRE_FALSE(command_queue->empty());
}
