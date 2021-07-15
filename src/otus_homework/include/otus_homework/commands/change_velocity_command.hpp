#pragma once
#include <memory>

#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_velocity_changable.hpp"

namespace tank_battle_server
{
	class change_velocity_command : public i_command
	{
	public:
		explicit change_velocity_command(std::shared_ptr<i_velocity_changable> velocity_changable);

		void execute() override;

	private:
		std::shared_ptr<i_velocity_changable> velocity_changable_;
	};
}
