#include <utility>
#include <stdexcept>

#include "otus_homework/commands/change_velocity_command.hpp"

namespace tank_battle_server
{
	change_velocity_command::change_velocity_command(std::shared_ptr<i_velocity_changable> velocity_changable)
		: velocity_changable_(std::move(velocity_changable))
	{
	}

	void change_velocity_command::execute()
	{
		try
		{
			const auto velocity = this->velocity_changable_->get_velocity();
			const auto velocity_change_shift = this->velocity_changable_->get_velocity_change_shift();
			const auto velocity_change_angle = this->velocity_changable_->get_velocity_change_angle();

			const auto shifted_velocity = velocity + velocity_change_shift;
			const auto changed_velocity = shifted_velocity.rotate(velocity_change_angle);
			
			this->velocity_changable_->set_velocity(changed_velocity);
		}
		catch (...)
		{
			throw std::runtime_error("command exception");
		}
	}
}
