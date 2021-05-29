#include "otus_homework/command_executor.hpp"

namespace tank_battle_server
{
	command_executor::command_executor(boost::lockfree::spsc_queue<std::shared_ptr<i_command>>& command_queue)
	{
		start(command_queue);
	}

	void command_executor::hard_stop()
	{
		stop();
	}

	void command_executor::soft_stop()
	{
		std::unique_lock<std::mutex> locker(this->soft_stop_locker_);

		while (this->is_started_)
		{
			this->soft_stop_cv_.wait(locker);
		}
	}

	command_executor::~command_executor()
	{
		stop();
		this->command_executor_thread_.join();
	}
	
	void command_executor::start(lf::spsc_queue<std::shared_ptr<i_command>>& command_queue)
	{
		this->is_started_ = true;
		
		this->command_executor_thread_ = std::thread([&]()
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

						if (command_queue.empty())
						{
							stop();
							this->soft_stop_cv_.notify_one();
						}
					}
					catch(...)
					{
						
					}
				}
			}
		);
	}

	void command_executor::stop()
	{
		this->is_started_ = false;
	}
}
