#include "otus_homework/commands/initialize_tank_command.hpp"

#include "otus_homework/globals.hpp"

namespace tank_battle_server
{
	initialize_tank_command::initialize_tank_command(std::shared_ptr<i_uobject> obj,
	                                                 std::list<std::string> command_names)
		: obj_(std::move(obj)), command_names_(std::move(command_names))
	{
	}

	void initialize_tank_command::execute()
	{
		for (auto const& command_name : this->command_names_)
		{
			ioc_provider::IoC.resolve<i_command>(command_name, this->obj_)->execute();
		}
	}
}
