#include "otus_homework/commands/hard_stop_command.hpp"

namespace tank_battle_server
{
	hard_stop_command::hard_stop_command(std::shared_ptr<std::shared_ptr<i_state>> state)
		: state_(std::move(state))
	{
	}

	void hard_stop_command::execute()
	{
		*this->state_ = nullptr;
	}
}
