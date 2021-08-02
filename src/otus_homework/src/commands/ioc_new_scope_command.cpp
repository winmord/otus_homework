#include "otus_homework/commands/ioc_new_scope_command.hpp"

namespace tank_battle_server
{
	ioc_new_scope_command::ioc_new_scope_command(std::shared_ptr<std::string> scope_id,
	                                             std::shared_ptr<ioc_storage> container)
		: scope_id_(std::move(scope_id)),
		  container_(std::move(container))
	{
	}

	void ioc_new_scope_command::execute()
	{
		this->container_->insert_scope(this->scope_id_);
	}
}
