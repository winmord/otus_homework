#pragma once
#include <otus_homework/movement_vector.hpp>

namespace tank_battle_server
{
	class i_rotatable
	{
	public:
		virtual ~i_rotatable() = default;
		virtual int get_direction() const = 0;
		virtual void set_direction(const int direction) = 0;
		virtual int get_angular_velocity() const = 0;
		virtual int get_max_directions() const = 0;
	};
}
