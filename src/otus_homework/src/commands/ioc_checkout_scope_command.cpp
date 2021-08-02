#include "otus_homework/commands/ioc_checkout_scope_command.hpp"

namespace tank_battle_server
{
	ioc_checkout_scope_command::ioc_checkout_scope_command(std::string scope_id,
	                                                       std::shared_ptr<std::string> current_scope)
		: scope_id_(std::move(scope_id)),
		  current_scope_(std::move(current_scope))
	{
	}

	void ioc_checkout_scope_command::execute()
	{
		current_scope_.reset();
		current_scope_ = std::make_shared<std::string>(scope_id_);
	}
}
