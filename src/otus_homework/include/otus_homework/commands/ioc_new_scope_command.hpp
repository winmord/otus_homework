#pragma once
#include <set>
#include <memory>
#include <string>

#include "otus_homework/interfaces/i_command.hpp"

#include "otus_homework/utils/ioc_storage.hpp"

namespace tank_battle_server
{
	class ioc_new_scope_command : public i_command
	{
	public:
		ioc_new_scope_command(std::shared_ptr<std::string> scope_id,
		                      std::shared_ptr<ioc_storage> container);

		void execute() override;

	private:
		std::shared_ptr<std::string> scope_id_;
		std::shared_ptr<ioc_storage> container_;
	};
}
