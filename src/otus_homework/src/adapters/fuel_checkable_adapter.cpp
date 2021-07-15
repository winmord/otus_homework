#include "otus_homework/adapters/fuel_checkable_adapter.hpp"

#include <utility>

namespace tank_battle_server
{
	fuel_checkable_adapter::fuel_checkable_adapter(std::shared_ptr<i_uobject> obj)
		: obj_(std::move(obj))
	{
	}

	int fuel_checkable_adapter::get_fuel_burn_velocity() const
	{
		return std::any_cast<int>(this->obj_->get_value(std::string("fuel_burn_velocity")));
	}

	int fuel_checkable_adapter::get_fuel_amount() const
	{
		return std::any_cast<int>(this->obj_->get_value(std::string("fuel_amount")));
	}
}
