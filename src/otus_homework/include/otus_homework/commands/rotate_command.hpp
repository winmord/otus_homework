#pragma once
#include <memory>

#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_rotatable.hpp"

namespace tank_battle_server
{
	class rotate_command : public i_command
	{
	public:
		explicit rotate_command(std::shared_ptr<i_rotatable> rotatable);
		
		void execute() override;

	private:
		std::shared_ptr<i_rotatable> rotatable_;
	};
}
