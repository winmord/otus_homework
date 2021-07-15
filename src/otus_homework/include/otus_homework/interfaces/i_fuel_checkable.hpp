#pragma once

namespace tank_battle_server
{
	class i_fuel_checkable
	{
	public:
		virtual ~i_fuel_checkable() = default;
		virtual int get_fuel_burn_velocity() const = 0;
		virtual int get_fuel_amount() const = 0;
	};
}
