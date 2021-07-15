#pragma once
#include <memory>

#include "otus_homework/interfaces/i_uobject.hpp"
#include "otus_homework/interfaces/i_velocity_changable.hpp"

namespace tank_battle_server
{
	class velocity_changable_adapter : public i_velocity_changable
	{
	public:
		velocity_changable_adapter(std::shared_ptr<i_uobject> obj);

		movement_vector get_velocity() const override;
		movement_vector get_velocity_change_shift() const override;
		double get_velocity_change_angle() const override;
		void set_velocity(movement_vector const& velocity) override;

	private:
		std::shared_ptr<i_uobject> obj_;
	};
}
