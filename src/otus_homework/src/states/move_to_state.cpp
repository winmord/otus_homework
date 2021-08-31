#include "otus_homework/states/move_to_state.hpp"

#include "otus_homework/commands/hard_stop_command.hpp"
#include "otus_homework/commands/run_command.hpp"

namespace tank_battle_server
{
	move_to_state::move_to_state(std::shared_ptr<std::shared_ptr<i_state>> state,
	                             std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue,
	                             std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> new_command_queue)
		: state_(std::move(state)),
		  command_queue_(std::move(command_queue)),
		  new_command_queue_(std::move(new_command_queue))
	{
	}

	void move_to_state::to()
	{
		const auto cmd = this->command_queue_->pop();

		if (std::dynamic_pointer_cast<hard_stop_command>(cmd) != nullptr ||
			std::dynamic_pointer_cast<run_command>(cmd) != nullptr)
		{
			cmd->execute();
		}
		else
		{
			this->new_command_queue_->push(cmd);
		}
	}
}
