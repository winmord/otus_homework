#pragma once
#include <memory>

#include "otus_homework/interfaces/i_rotatable.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"

namespace tank_battle_server
{
	class rotatable_adapter : public i_rotatable
	{
	public:
		rotatable_adapter(std::shared_ptr<i_uobject> obj);

		int get_direction() const override;
		void set_direction(const int direction) override;
		int get_angular_velocity() const override;
		int get_max_directions() const override;
	
	private:
		std::shared_ptr<i_uobject> obj_;
	};
}
