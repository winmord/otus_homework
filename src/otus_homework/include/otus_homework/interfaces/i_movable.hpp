#pragma once
#include <otus_homework/movement_vector.hpp>

namespace tank_battle_server
{
	class i_movable
	{
	public:
		virtual ~i_movable() = default;
		virtual movement_vector get_position() const = 0;
		virtual void set_position(movement_vector const& position) = 0;
		virtual movement_vector get_velocity() const = 0;
	};
}
