#include "otus_homework/commands/ioc_new_scope_command.hpp"

namespace tank_battle_server
{
	ioc_new_scope_command::ioc_new_scope_command(std::string scope_id,
	                                             std::shared_ptr<std::set<std::string>> scopes)
		: scope_id_(std::move(scope_id)),
		  scopes_(std::move(scopes))
	{
	}

	void ioc_new_scope_command::execute()
	{
		scopes_->insert(scope_id_);
	}
}
