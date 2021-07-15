#include "otus_homework/adapters/fuel_burnable_adapter.hpp"

#include <utility>

namespace tank_battle_server
{
	fuel_burnable_adapter::fuel_burnable_adapter(std::shared_ptr<i_uobject> obj)
		: obj_(std::move(obj))
	{
	}

	int fuel_burnable_adapter::get_fuel_burn_velocity() const
	{
		return std::any_cast<int>(this->obj_->get_value(std::string("fuel_burn_velocity")));
	}

	int fuel_burnable_adapter::get_fuel_amount() const
	{
		return std::any_cast<int>(this->obj_->get_value(std::string("fuel_amount")));
	}

	void fuel_burnable_adapter::set_fuel_amount(const int amount)
	{
		this->obj_->set_value("fuel_amount", amount);
	}
}
