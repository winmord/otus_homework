#include "otus_homework/command_executor.hpp"

namespace tank_battle_server
{
	command_executor::command_executor(std::shared_ptr<lf::spsc_queue<std::shared_ptr<i_command>>> command_queue)
		: command_queue_(std::move(command_queue))
	{
		start();
	}

	void command_executor::hard_stop()
	{
		stop();
	}

	void command_executor::soft_stop() const
	{
		class soft_stop_command : public i_command
		{
		public:
			void execute() override
			{
				throw std::runtime_error("soft stop");
			}
		};

		const auto soft_stop_cmd = std::make_shared<soft_stop_command>();

		while (!this->command_queue_->push(soft_stop_cmd))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	bool command_executor::is_started() const
	{
		return this->is_started_;
	}

	command_executor::~command_executor()
	{
		stop();
		this->command_executor_thread_.join();
	}

	void command_executor::start()
	{
		this->is_started_ = true;

		this->command_executor_thread_ = std::thread([&]()
			{
				while (this->is_started_)
				{
					this->command_queue_->consume_one([&](std::shared_ptr<i_command> const& cmd)
						{
							try
							{
								cmd->execute();
							}
							catch (std::exception& exc)
							{
								if (exc.what() == std::string("soft stop"))
								{
									stop();
								}
							}
						}
					);
				}
			}
		);
	}

	void command_executor::stop()
	{
		this->is_started_ = false;
	}
}
