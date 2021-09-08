#pragma once

#include "otus_homework/interfaces/i_command.hpp"

#include <memory>

#include "otus_homework/interfaces/i_uobject.hpp"
#include "otus_homework/movement_vector.hpp"

namespace tank_battle_server
{
	class setup_tank_position_command : public i_command
	{
	public:
		explicit setup_tank_position_command(std::shared_ptr<i_uobject> obj,
		                                     movement_vector position);

		void execute() override;

	private:
		std::shared_ptr<i_uobject> obj_;
		movement_vector position_;
	};
}
