#pragma once
#include <memory>

#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_fuel_burnable.hpp"

namespace tank_battle_server
{
	class burn_fuel_command: public i_command
	{
	public:
		explicit burn_fuel_command(std::shared_ptr<i_fuel_burnable> fuel_burnable);

		void execute() override;

	private:
		std::shared_ptr<i_fuel_burnable> fuel_burnable_;
	};
}