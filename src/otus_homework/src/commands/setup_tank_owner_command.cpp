#include "otus_homework/commands/setup_tank_owner_command.hpp"

namespace tank_battle_server
{
	setup_tank_owner_command::setup_tank_owner_command(std::shared_ptr<i_uobject> obj,
	                                                   const int owner_number)
		: obj_(std::move(obj)), owner_number_(owner_number)
	{
	}

	void setup_tank_owner_command::execute()
	{
		this->obj_->set_value(std::string("owner"), this->owner_number_);
	}
}
