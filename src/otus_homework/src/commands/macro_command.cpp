#include "otus_homework/commands/macro_command.hpp"

#include <stdexcept>

namespace tank_battle_server
{
	macro_command::macro_command(std::list<std::shared_ptr<i_command>> const& commands)
		: commands_(commands)
	{
	}

	void macro_command::execute()
	{
		try
		{
			for(auto const& command : this->commands_)
			{
				command->execute();
			}
		}
		catch (...)
		{
			throw std::runtime_error("command exception");
		}
	}
}
