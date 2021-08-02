#pragma once
#include <set>
#include <memory>
#include <string>

#include "otus_homework/interfaces/i_command.hpp"

namespace tank_battle_server
{
	class ioc_new_scope_command : public i_command
	{
	public:
		ioc_new_scope_command(std::string scope_id,
			std::shared_ptr<std::set<std::string>> scopes);

		void execute() override;

	private:
		std::string scope_id_;
		std::shared_ptr<std::set<std::string>> scopes_;
	};
}
