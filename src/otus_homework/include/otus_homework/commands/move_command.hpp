#pragma once
#include <memory>

#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_movable.hpp"

namespace tank_battle_server
{
	class move_command : public i_command
	{
	public:
		explicit move_command(std::shared_ptr<i_movable> movable);
		
		void execute() override;

	private:
		std::shared_ptr<i_movable> movable_;
	};
}
