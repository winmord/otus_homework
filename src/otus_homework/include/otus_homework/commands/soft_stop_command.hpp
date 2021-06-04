#pragma once
#include "otus_homework/interfaces/i_command.hpp"

namespace tank_battle_server
{
	class soft_stop_command : public i_command
	{
	public:
		void execute() override;
	};
}
