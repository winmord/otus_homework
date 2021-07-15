#include "otus_homework/commands/burn_fuel_command.hpp"

#include <stdexcept>
#include <utility>

namespace tank_battle_server
{
	burn_fuel_command::burn_fuel_command(std::shared_ptr<i_fuel_burnable> fuel_burnable)
		: fuel_burnable_(std::move(fuel_burnable))
	{
	}

	void burn_fuel_command::execute()
	{
		try
		{
			const auto fuel_amount = this->fuel_burnable_->get_fuel_amount();
			const auto fuel_burn_velocity = this->fuel_burnable_->get_fuel_burn_velocity();
			const auto current_fuel_amount = fuel_amount - fuel_burn_velocity;

			if (current_fuel_amount < 0) throw std::runtime_error("there is no fuel for burning");
			
			this->fuel_burnable_->set_fuel_amount(current_fuel_amount);
		}
		catch(...)
		{
			throw std::runtime_error("command exception");
		}
	}
}
