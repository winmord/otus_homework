#pragma once
#include <memory>
#include <string>

#include "otus_homework/interfaces/i_command.hpp"

namespace tank_battle_server
{
	class ioc_checkout_scope_command : public i_command
	{
	public:
		ioc_checkout_scope_command(std::string scope_id,
		                           std::shared_ptr<std::string> current_scope,
		                           std::shared_ptr<int> objects_count,
		                           std::shared_ptr<int> player_1_object_position,
		                           std::shared_ptr<int> player_2_object_position);

		void execute() override;

	private:
		std::string scope_id_;
		std::shared_ptr<std::string> current_scope_;
		std::shared_ptr<int> objects_count_;
		std::shared_ptr<int> player_1_object_position_;
		std::shared_ptr<int> player_2_object_position_;
	};
}
