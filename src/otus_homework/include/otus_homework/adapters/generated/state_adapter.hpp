#pragma once
#include <memory>

#include "otus_homework/globals.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"
#include "otus_homework/interfaces/i_state.hpp"

namespace tank_battle_server
{
	class state_adapter : public i_state
	{
	public:
		explicit state_adapter(std::shared_ptr<i_uobject> obj)
			: obj_(std::move(obj))
		{}

	private:
		std::shared_ptr<i_uobject> obj_;
	};
}