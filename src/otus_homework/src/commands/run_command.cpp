#include "otus_homework/commands/run_command.hpp"

#include "otus_homework/states/usual_state.hpp"

namespace tank_battle_server
{
	run_command::run_command(std::shared_ptr<std::shared_ptr<i_state>> state,
	                         std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue)
		: state_(std::move(state)), command_queue_(std::move(command_queue))
	{
	}

	void run_command::execute()
	{
		*this->state_ = std::make_shared<usual_state>(this->command_queue_);
	}
}
