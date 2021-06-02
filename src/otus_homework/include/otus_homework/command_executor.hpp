#pragma once

#include <condition_variable>
#include <memory>
#include <thread>

#include <boost/lockfree/spsc_queue.hpp>

#include "otus_homework/interfaces/i_command.hpp"

namespace lf = boost::lockfree;


namespace tank_battle_server
{
	class command_executor
	{
	public:
		explicit command_executor(std::shared_ptr<lf::spsc_queue<std::shared_ptr<i_command>>> command_queue);

		void hard_stop();
		void soft_stop() const;

		bool is_started() const;
		
		~command_executor();

	private:
		void start();
		void stop();

		std::shared_ptr<lf::spsc_queue<std::shared_ptr<i_command>>> command_queue_;
		std::thread command_executor_thread_;
		bool is_started_{false};
	};
}
