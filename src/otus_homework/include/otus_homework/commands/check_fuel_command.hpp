#pragma once
#include <memory>

#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_fuel_checkable.hpp"

namespace tank_battle_server
{
	class check_fuel_command : public i_command
	{
	public:
		explicit check_fuel_command(std::shared_ptr<i_fuel_checkable> fuel_checkable);

		void execute() override;

	private:
		std::shared_ptr<i_fuel_checkable> fuel_checkable_;
	};
}