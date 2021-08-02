#include "otus_homework/commands/ioc_unregister_command.hpp"

namespace tank_battle_server
{
	ioc_unregister_command::ioc_unregister_command(std::string key,
	                                               std::shared_ptr<std::string> scope_id,
	                                               std::shared_ptr<ioc_storage> container)
		: key_(std::move(key)),
		  scope_id_(std::move(scope_id)),
		  container_(std::move(container))
	{
	}

	void ioc_unregister_command::execute()
	{
		this->container_->remove_dependency(this->scope_id_, this->key_);
	}
}
