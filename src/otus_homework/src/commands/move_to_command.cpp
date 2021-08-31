#include "otus_homework/commands/move_to_command.hpp"

#include "otus_homework/states/move_to_state.hpp"

namespace tank_battle_server
{
	move_to_command::move_to_command(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                 std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue,
	                                 std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> new_command_queue)
		: state_(std::move(state)),
		  command_queue_(std::move(command_queue)),
		  new_command_queue_(std::move(new_command_queue))
	{
	}

	void move_to_command::execute()
	{
		*this->state_ = std::make_shared<move_to_state>(state_, command_queue_, new_command_queue_);
	}
}
