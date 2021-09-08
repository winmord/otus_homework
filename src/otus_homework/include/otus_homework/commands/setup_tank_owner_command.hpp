#pragma once

#include "otus_homework/interfaces/i_command.hpp"

#include <memory>

#include "otus_homework/interfaces/i_uobject.hpp"

namespace tank_battle_server
{
	class setup_tank_owner_command : public i_command
	{
	public:
		explicit setup_tank_owner_command(std::shared_ptr<i_uobject> obj,
		                                  const int owner_number);

		void execute() override;

	private:
		std::shared_ptr<i_uobject> obj_;
		int owner_number_;
	};
}
