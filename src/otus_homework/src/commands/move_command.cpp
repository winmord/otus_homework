#include <utility>

#include "otus_homework/commands/move_command.hpp"

namespace tank_battle_server
{
	move_command::move_command(std::shared_ptr<i_movable> movable)
		: movable_(std::move(movable))
	{
	}

	void move_command::execute()
	{
		movable_->set_position(movable_->get_position() + movable_->get_velocity());
	}
}
