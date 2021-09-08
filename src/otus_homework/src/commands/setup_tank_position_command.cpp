#include "otus_homework/commands/setup_tank_position_command.hpp"

namespace tank_battle_server
{
	setup_tank_position_command::setup_tank_position_command(std::shared_ptr<i_uobject> obj,
	                                                         movement_vector position)
		: obj_(std::move(obj)), position_(std::move(position))
	{
	}

	void setup_tank_position_command::execute()
	{
		this->obj_->set_value(std::string("position"), this->position_);
	}
}
