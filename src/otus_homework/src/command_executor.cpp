#include "otus_homework/command_executor.hpp"

namespace tank_battle_server
{
	command_executor::command_executor(boost::lockfree::spsc_queue<std::shared_ptr<i_command>>& command_queue)
	{
		start(command_queue);
	}

	command_executor::~command_executor()
	{
		stop();
	}
	
	void command_executor::start(lf::spsc_queue<std::shared_ptr<i_command>>& command_queue)
	{
		this->is_started_ = true;
		
		std::thread command_executor_thread([&]()
			{
				while (this->is_started_)
				{
					try
					{		
						command_queue.consume_one([](std::shared_ptr<i_command> cmd)
							{
								cmd->execute();
							}
						);

						if (command_queue.empty()) stop();
					}
					catch(...)
					{
						
					}
				}
			}
		);

		command_executor_thread.detach();
	}

	void command_executor::stop()
	{
		this->is_started_ = false;
	}
}
