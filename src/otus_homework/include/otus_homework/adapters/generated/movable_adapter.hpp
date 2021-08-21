#pragma once
#include <memory>

#include "otus_homework/globals.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"
#include "otus_homework/interfaces/i_movable.hpp"

namespace tank_battle_server
{
	class movable_adapter : public i_movable
	{
	public:
		explicit movable_adapter(std::shared_ptr<i_uobject> obj)
			: obj_(std::move(obj))
		{}

		movement_vector get_position() const override
		{
			return *ioc_provider::IoC.resolve<movement_vector>("tank.operations.i_movable:get_position", obj_);
		}

		void set_position(movement_vector const& position) override
		{
			ioc_provider::IoC.resolve("tank.operations.i_movable:set_position", obj_, position);
		}

		movement_vector get_velocity() const override
		{
			return *ioc_provider::IoC.resolve<movement_vector>("tank.operations.i_movable:get_velocity", obj_);
		}

	private:
		std::shared_ptr<i_uobject> obj_;
	};
}