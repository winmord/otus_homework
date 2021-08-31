#pragma once

#include <memory>

#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_state.hpp"

namespace tank_battle_server
{
	class hard_stop_command : public i_command
	{
	public:
		explicit hard_stop_command(std::shared_ptr<std::shared_ptr<i_state>> state);
		
		void execute() override;

	private:
		std::shared_ptr<std::shared_ptr<i_state>> state_;
	};
}
