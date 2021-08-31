#include "otus_homework/states/usual_state.hpp"

namespace tank_battle_server
{
	usual_state::usual_state(std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue)
		: command_queue_(std::move(command_queue))
	{
	}

	void usual_state::to()
	{
		auto cmd = this->command_queue_->pop();
		cmd->execute();
	}
}
