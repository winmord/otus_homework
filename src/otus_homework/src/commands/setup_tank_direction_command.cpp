#include "otus_homework/commands/setup_tank_direction_command.hpp"

namespace tank_battle_server
{
	setup_tank_direction_command::setup_tank_direction_command(std::shared_ptr<i_uobject> obj,
	                                                           const int direction)
		: obj_(std::move(obj)), direction_(direction)
	{
	}

	void setup_tank_direction_command::execute()
	{
		this->obj_->set_value(std::string("direction"), this->direction_);
	}
}
