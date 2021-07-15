#pragma once
#include <memory>

#include "otus_homework/interfaces/i_fuel_checkable.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"

namespace tank_battle_server
{
	class fuel_checkable_adapter : public i_fuel_checkable
	{
	public:
		explicit fuel_checkable_adapter(std::shared_ptr<i_uobject> obj);

		int get_fuel_burn_velocity() const override;
		int get_fuel_amount() const override;
		
	private:
		std::shared_ptr<i_uobject> obj_;
	};
}
