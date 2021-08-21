#pragma once
#include <memory>

#include "otus_homework/globals.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"
#include "otus_homework/interfaces/i_fuel_burnable.hpp"

namespace tank_battle_server
{
	class fuel_burnable_adapter : public i_fuel_burnable
	{
	public:
		explicit fuel_burnable_adapter(std::shared_ptr<i_uobject> obj)
			: obj_(std::move(obj))
		{}

		int get_fuel_burn_velocity() const override
		{
			return *ioc_provider::IoC.resolve<int>("tank.operations.i_fuel_burnable:get_fuel_burn_velocity", obj_);
		}

		int get_fuel_amount() const override
		{
			return *ioc_provider::IoC.resolve<int>("tank.operations.i_fuel_burnable:get_fuel_amount", obj_);
		}

		void set_fuel_amount(const int amount) override
		{
			ioc_provider::IoC.resolve("tank.operations.i_fuel_burnable:set_fuel_amount", obj_, amount);
		}

	private:
		std::shared_ptr<i_uobject> obj_;
	};
}