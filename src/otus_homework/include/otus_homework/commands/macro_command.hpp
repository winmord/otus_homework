#pragma once

#include "otus_homework/interfaces/i_command.hpp"

#include <memory>
#include <list>

namespace tank_battle_server
{
	class macro_command: public i_command
	{
	public:
		explicit macro_command(std::list<std::shared_ptr<i_command>> const& commands);

		void execute() override;

	private:
		std::list<std::shared_ptr<i_command>> const& commands_;
	};
}
