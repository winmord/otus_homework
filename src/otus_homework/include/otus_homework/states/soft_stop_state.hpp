#pragma once

#include <memory>

#include "otus_homework/blocking_queue.hpp"
#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_state.hpp"

namespace tank_battle_server
{
	class soft_stop_state : public i_state
	{
	public:
		soft_stop_state(std::shared_ptr<std::shared_ptr<i_state>> state,
		                std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue);
		
		void to() override;

	private:

		std::shared_ptr<std::shared_ptr<i_state>> state_;
		std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue_;
	};
}
