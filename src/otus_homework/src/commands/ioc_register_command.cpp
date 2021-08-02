#include <utility>

#include "otus_homework/commands/ioc_register_command.hpp"

namespace tank_battle_server
{
	ioc_register_command::ioc_register_command(std::string key,
	                                           std::any function,
	                                           std::shared_ptr<std::string> scope_id,
	                                           std::shared_ptr<ioc_storage> container)
		: key_(std::move(key)),
		  function_(std::move(function)),
		  scope_id_(std::move(scope_id)),
		  container_(std::move(container))
	{
	}

	void ioc_register_command::execute()
	{
		this->container_->insert_dependency(this->scope_id_, this->key_, this->function_);
	}
}
