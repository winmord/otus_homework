#pragma once
#include <memory>

#include "otus_homework/interfaces/i_fuel_burnable.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"

namespace tank_battle_server
{
	class fuel_burnable_adapter : public i_fuel_burnable
	{
	public:
		explicit fuel_burnable_adapter(std::shared_ptr<i_uobject> obj);

		int get_fuel_burn_velocity() const override;
		int get_fuel_amount() const override;
		void set_fuel_amount(const int amount) override;
		
	private:
		std::shared_ptr<i_uobject> obj_;
	};
}
