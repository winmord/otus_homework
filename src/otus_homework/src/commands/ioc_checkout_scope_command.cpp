#include "otus_homework/commands/ioc_checkout_scope_command.hpp"

namespace tank_battle_server
{
	ioc_checkout_scope_command::ioc_checkout_scope_command(std::string scope_id,
	                                                       std::shared_ptr<std::string> current_scope,
	                                                       std::shared_ptr<int> objects_count,
	                                                       std::shared_ptr<int> player_1_object_position,
	                                                       std::shared_ptr<int> player_2_object_position)
		: scope_id_(std::move(scope_id)),
		  current_scope_(std::move(current_scope)),
		  objects_count_(std::move(objects_count)),
		  player_1_object_position_(std::move(player_1_object_position)),
		  player_2_object_position_(std::move(player_2_object_position))
	{
	}

	void ioc_checkout_scope_command::execute()
	{
		*this->current_scope_ = this->scope_id_;
		*this->objects_count_ = 0;
		*this->player_1_object_position_ = 0;
		*this->player_2_object_position_ = 0;
	}
}
