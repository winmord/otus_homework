#include "include/common_test_functions.hpp"

#include <mutex>

#include <otus_homework/command_executor.hpp>

namespace tank_battle_server
{
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
}
