#include <utility>

#include "otus_homework/adapters/rotatable_adapter.hpp"

namespace tank_battle_server
{
	rotatable_adapter::rotatable_adapter(std::shared_ptr<i_uobject> obj)
		: obj_(std::move(obj))
	{
	}

	int rotatable_adapter::get_direction() const
	{
		return std::any_cast<int>(this->obj_->get_value(std::string("direction")));
	}

	void rotatable_adapter::set_direction(const int direction)
	{
		this->obj_->set_value("direction", direction);
	}

	int rotatable_adapter::get_angular_velocity() const
	{
		return std::any_cast<int>(this->obj_->get_value(std::string("angular_velocity")));
	}

	int rotatable_adapter::get_max_directions() const
	{
		return std::any_cast<int>(this->obj_->get_value(std::string("max_directions")));
	}
}
