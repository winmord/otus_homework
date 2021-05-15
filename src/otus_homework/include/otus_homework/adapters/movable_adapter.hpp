#pragma once
#include <memory>

#include "otus_homework/interfaces/i_movable.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"

namespace tank_battle_server
{
	class movable_adapter : public i_movable
	{
	public:
		movable_adapter(std::shared_ptr<i_uobject> obj);

		movement_vector get_position() const override;
		void set_position(movement_vector const& position) override;
		
		movement_vector get_velocity() const override;
	
	private:
		std::shared_ptr<i_uobject> obj_;
	};
}
