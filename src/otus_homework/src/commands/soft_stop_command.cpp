#include "otus_homework/commands/soft_stop_command.hpp"

#include "otus_homework/states/soft_stop_state.hpp"

namespace tank_battle_server
{
	soft_stop_command::soft_stop_command(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                     std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue)
		: state_(std::move(state)), command_queue_(std::move(command_queue))
	{
	}

	void soft_stop_command::execute()
	{
		*this->state_ = std::make_shared<soft_stop_state>(this->state_, this->command_queue_);
	}
}
