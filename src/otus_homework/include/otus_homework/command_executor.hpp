#pragma once

#include <condition_variable>
#include <memory>
#include <thread>

#include "interfaces/i_state.hpp"
#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/blocking_queue.hpp"


namespace tank_battle_server
{
	class command_executor
	{
	public:
		explicit command_executor(std::shared_ptr<std::shared_ptr<i_state>> state,
		                          std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue);

		bool is_started() const;

		~command_executor();

	private:
		void start();
		void stop();

		void process_hard_stop(std::string const& what);
		void process_soft_stop(std::string const& what);
		void check_soft_stop();

		std::shared_ptr<std::shared_ptr<i_state>> state_;
		std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue_;
		std::thread command_executor_thread_;
		bool is_started_{false};

		bool soft_stopping_in_process_{false};
	};
}
