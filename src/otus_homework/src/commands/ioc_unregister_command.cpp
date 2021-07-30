#include "otus_homework/commands/ioc_unregister_command.hpp"

namespace tank_battle_server
{
	ioc_unregister_command::ioc_unregister_command(std::string key,
	                                               std::shared_ptr<std::map<std::string, std::any>> container)
		: key_(std::move(key)),
		  container_(std::move(container))
	{
	}

	void ioc_unregister_command::execute()
	{
		this->container_->erase(this->key_);
	}
}
