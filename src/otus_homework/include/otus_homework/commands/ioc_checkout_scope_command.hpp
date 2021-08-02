#pragma once
#include <any>
#include <map>
#include <memory>
#include <string>

#include "otus_homework/interfaces/i_command.hpp"

namespace tank_battle_server
{
	class ioc_checkout_scope_command : public i_command
	{
	public:
		ioc_checkout_scope_command(std::string scope_id,
		                           std::shared_ptr<std::string> current_scope);

		void execute() override;

	private:
		std::string scope_id_;
		std::shared_ptr<std::string> current_scope_;
	};
}
