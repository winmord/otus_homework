#include "otus_homework/commands/ioc_register_command.hpp"

namespace tank_battle_server
{
	ioc_register_command::ioc_register_command(std::string key, std::any function,
	                                   std::shared_ptr<std::map<std::string, std::any>> container)
		: key_(std::move(key)),
		  function_(std::move(function)),
		  container_(std::move(container))
	{
	}

	void ioc_register_command::execute()
	{
		this->container_->emplace(this->key_, this->function_);
	}
}
