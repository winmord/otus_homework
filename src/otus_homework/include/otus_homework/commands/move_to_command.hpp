#pragma once

#include <memory>

#include "otus_homework/blocking_queue.hpp"
#include "otus_homework/interfaces/i_command.hpp"
#include "otus_homework/interfaces/i_state.hpp"

namespace tank_battle_server
{
	class move_to_command : public i_command
	{
	public:
		explicit move_to_command(std::shared_ptr<std::shared_ptr<i_state>> state,
		                         std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue,
		                         std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> new_command_queue);

		void execute() override;

	private:
		std::shared_ptr<std::shared_ptr<i_state>> state_;
		std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> command_queue_;
		std::shared_ptr<blocking_queue<std::shared_ptr<i_command>>> new_command_queue_;
	};
}
