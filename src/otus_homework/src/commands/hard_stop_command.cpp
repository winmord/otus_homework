#include "otus_homework/commands/hard_stop_command.hpp"

#include <stdexcept>

namespace tank_battle_server
{
	void hard_stop_command::execute()
	{
		throw std::runtime_error("hard stop");
	}
}
