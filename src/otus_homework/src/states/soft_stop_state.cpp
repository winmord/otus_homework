#include "otus_homework/states/soft_stop_state.hpp"

namespace tank_battle_server
{
	soft_stop_state::soft_stop_state(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                 std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue)
		: state_(std::move(state)), command_queue_(std::move(command_queue))
	{
	}

	void soft_stop_state::to()
	{
		if(!this->command_queue_->empty())
		{
			auto cmd = this->command_queue_->pop();
			cmd->execute();
		}
		else
		{
			*this->state_ = nullptr;
		}
	}
}
