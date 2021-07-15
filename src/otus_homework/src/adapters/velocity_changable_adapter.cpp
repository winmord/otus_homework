#include <utility>

#include "otus_homework/adapters/velocity_changable_adapter.hpp"

namespace tank_battle_server
{
	velocity_changable_adapter::velocity_changable_adapter(std::shared_ptr<i_uobject> obj)
		: obj_(std::move(obj))
	{
	}

	movement_vector velocity_changable_adapter::get_velocity() const
	{
		return std::any_cast<movement_vector>(this->obj_->get_value(std::string("velocity")));
	}
	
	movement_vector velocity_changable_adapter::get_velocity_change_shift() const
	{
		return std::any_cast<movement_vector>(this->obj_->get_value(std::string("velocity_change_shift")));
	}

	double velocity_changable_adapter::get_velocity_change_angle() const
	{
		return std::any_cast<double>(this->obj_->get_value(std::string("velocity_change_angle")));
	}

	void velocity_changable_adapter::set_velocity(movement_vector const& velocity)
	{
		this->obj_->set_value("velocity", velocity);
	}
}
