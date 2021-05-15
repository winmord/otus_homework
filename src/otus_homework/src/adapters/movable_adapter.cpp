#include <utility>

#include "otus_homework/adapters/movable_adapter.hpp"

namespace tank_battle_server
{
	movable_adapter::movable_adapter(std::shared_ptr<i_uobject> obj)
		: obj_(std::move(obj))
	{
	}

	movement_vector movable_adapter::get_position() const
	{
		return std::any_cast<movement_vector>(this->obj_->get_value(std::string("position")));
	}

	void movable_adapter::set_position(movement_vector const& position)
	{
		this->obj_->set_value("position", position);
	}

	movement_vector movable_adapter::get_velocity() const
	{
		return std::any_cast<movement_vector>(this->obj_->get_value(std::string("velocity")));
	}
}
