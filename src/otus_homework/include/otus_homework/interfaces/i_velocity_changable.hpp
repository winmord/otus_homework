#pragma once
#include "otus_homework/movement_vector.hpp"

namespace tank_battle_server
{
	class i_velocity_changable
	{
	public:
		virtual ~i_velocity_changable() = default;
		virtual movement_vector get_velocity() const = 0;
		virtual movement_vector get_velocity_change_shift() const = 0;
		virtual double get_velocity_change_angle() const = 0;
		virtual void set_velocity(movement_vector const& velocity) = 0;
	};
}
