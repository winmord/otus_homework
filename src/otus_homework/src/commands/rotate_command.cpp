#include <utility>
#include <stdexcept>

#include "otus_homework/commands/rotate_command.hpp"

namespace tank_battle_server
{
	rotate_command::rotate_command(std::shared_ptr<i_rotatable> rotatable)
		: rotatable_(std::move(rotatable))
	{
	}

	void rotate_command::execute()
	{
		try
		{
			rotatable_->set_direction(
				(rotatable_->get_direction() + rotatable_->get_angular_velocity()) % rotatable_->get_max_directions());
		}
		catch(...)
		{
			throw std::runtime_error("command exception");
		}
	}
}
