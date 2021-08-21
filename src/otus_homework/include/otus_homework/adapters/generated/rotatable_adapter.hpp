#pragma once
#include <memory>

#include "otus_homework/globals.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"
#include "otus_homework/interfaces/i_rotatable.hpp"

namespace tank_battle_server
{
	class rotatable_adapter : public i_rotatable
	{
	public:
		explicit rotatable_adapter(std::shared_ptr<i_uobject> obj)
			: obj_(std::move(obj))
		{}

		int get_direction() const override
		{
			return *ioc_provider::IoC.resolve<int>("tank.operations.i_rotatable:get_direction", obj_);
		}

		void set_direction(const int direction) override
		{
			ioc_provider::IoC.resolve("tank.operations.i_rotatable:set_direction", obj_, direction);
		}

		int get_angular_velocity() const override
		{
			return *ioc_provider::IoC.resolve<int>("tank.operations.i_rotatable:get_angular_velocity", obj_);
		}

		int get_max_directions() const override
		{
			return *ioc_provider::IoC.resolve<int>("tank.operations.i_rotatable:get_max_directions", obj_);
		}

	private:
		std::shared_ptr<i_uobject> obj_;
	};
}