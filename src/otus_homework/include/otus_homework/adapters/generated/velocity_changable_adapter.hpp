#pragma once
#include <memory>

#include "otus_homework/globals.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"
#include "otus_homework/interfaces/i_velocity_changable.hpp"

namespace tank_battle_server
{
	class velocity_changable_adapter : public i_velocity_changable
	{
	public:
		explicit velocity_changable_adapter(std::shared_ptr<i_uobject> obj)
			: obj_(std::move(obj))
		{}

		movement_vector get_velocity() const override
		{
			return *ioc_provider::IoC.resolve<movement_vector>("tank.operations.i_velocity_changable:get_velocity", obj_);
		}

		movement_vector get_velocity_change_shift() const override
		{
			return *ioc_provider::IoC.resolve<movement_vector>("tank.operations.i_velocity_changable:get_velocity_change_shift", obj_);
		}

		double get_velocity_change_angle() const override
		{
			return *ioc_provider::IoC.resolve<double>("tank.operations.i_velocity_changable:get_velocity_change_angle", obj_);
		}

		void set_velocity(movement_vector const& velocity) override
		{
			ioc_provider::IoC.resolve("tank.operations.i_velocity_changable:set_velocity", obj_, velocity);
		}

	private:
		std::shared_ptr<i_uobject> obj_;
	};
}