#include "otus_homework/commands/soft_stop_command.hpp"

#include <stdexcept>

namespace tank_battle_server
{
	void soft_stop_command::execute()
	{
		throw std::runtime_error("soft stop");
	}
}
