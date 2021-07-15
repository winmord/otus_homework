#pragma once

namespace tank_battle_server
{
	class i_fuel_burnable
	{
	public:
		virtual ~i_fuel_burnable() = default;
		virtual int get_fuel_burn_velocity() const = 0;
		virtual int get_fuel_amount() const = 0;
		virtual void set_fuel_amount(const int amount) = 0;
	};
}
