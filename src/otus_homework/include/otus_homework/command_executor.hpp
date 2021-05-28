#pragma once
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
		explicit command_executor(lf::spsc_queue<std::shared_ptr<i_command>>& command_queue);

		~command_executor();

	private:
		void start(lf::spsc_queue<std::shared_ptr<i_command>>& command_queue);
		void stop();
		
		bool is_started_{false};
	};
}
