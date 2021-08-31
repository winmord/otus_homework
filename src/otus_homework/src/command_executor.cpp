#include "otus_homework/command_executor.hpp"

#include <future>

namespace tank_battle_server
{
	command_executor::command_executor(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                   std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue)
		: state_(std::move(state)), command_queue_(std::move(command_queue))
	{
		start();
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
				while (*this->state_ != nullptr)
				{
					this->state_->get()->to();
				}

				this->is_started_ = false;
			}
		);
	}

	void command_executor::stop()
	{
		this->is_started_ = false;
	}

	void command_executor::process_hard_stop(std::string const& what)
	{
		if (what == std::string("hard stop"))
		{
			stop();
		}
	}

	void command_executor::process_soft_stop(std::string const& what)
	{
		if (what == std::string("soft stop"))
		{
			this->soft_stopping_in_process_ = true;

			auto soft_stop_by_timeout = std::thread([&]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				stop();
			});

			soft_stop_by_timeout.detach();
		}
	}

	void command_executor::check_soft_stop()
	{
		if (this->soft_stopping_in_process_)
		{
			if (this->command_queue_->empty())
			{
				stop();
			}
		}
	}
}
