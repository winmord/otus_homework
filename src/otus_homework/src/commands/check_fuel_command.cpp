#include "otus_homework/commands/check_fuel_command.hpp"

#include <stdexcept>
#include <utility>

namespace tank_battle_server
{
	check_fuel_command::check_fuel_command(std::shared_ptr<i_fuel_checkable> fuel_checkable)
		: fuel_checkable_(std::move(fuel_checkable))
	{
	}

	void check_fuel_command::execute()
	{
		try
		{
			const auto fuel_amount = this->fuel_checkable_->get_fuel_amount();
			const auto fuel_burn_velocity = this->fuel_checkable_->get_fuel_burn_velocity();

			if(fuel_amount - fuel_burn_velocity < 0) throw std::runtime_error("running out of fuel");
		}
		catch (...)
		{
			throw std::runtime_error("command exception");
		}
	}
}
