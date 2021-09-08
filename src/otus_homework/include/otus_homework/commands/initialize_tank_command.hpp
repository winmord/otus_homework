#pragma once

#include "otus_homework/interfaces/i_command.hpp"

#include <list>
#include <memory>
#include <string>

#include "otus_homework/interfaces/i_uobject.hpp"

namespace tank_battle_server
{
	class initialize_tank_command : public i_command
	{
	public:
		initialize_tank_command(std::shared_ptr<i_uobject> obj,
		                        std::list<std::string> command_names);

		void execute() override;

	private:
		std::shared_ptr<i_uobject> obj_;
		std::list<std::string> command_names_;
	};
}
