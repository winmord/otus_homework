#pragma once

#include <memory>

#include "otus_homework/blocking_queue.hpp"
#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_state.hpp"

namespace tank_battle_server
{
	class usual_state : public i_state
	{
	public:
		usual_state(std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue);
		void to() override;

	private:
		std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue_;
	};
}
