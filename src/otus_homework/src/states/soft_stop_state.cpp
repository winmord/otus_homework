#include "otus_homework/states/soft_stop_state.hpp"

#include "otus_homework/commands/hard_stop_command.hpp"

namespace tank_battle_server
{
	soft_stop_state::soft_stop_state(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                 std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue)
		: state_(std::move(state)), command_queue_(std::move(command_queue))
	{
	}

	void soft_stop_state::to()
	{
		if (!this->command_queue_->empty())
		{
			const auto start = std::chrono::steady_clock::now();
			
			auto cmd = this->command_queue_->pop();
			cmd->execute();

			const auto end = std::chrono::steady_clock::now();
			const auto diff = end - start;

			this->total_execution_time_ += std::chrono::duration<double, std::milli>(diff).count();

			if(this->total_execution_time_ >= 1000) *this->state_ = nullptr;
		}
		else
		{
			*this->state_ = nullptr;
		}
	}
}
