#pragma once
#include <any>
#include <map>
#include <memory>
#include <string>

#include "otus_homework/interfaces/i_command.hpp"

namespace tank_battle_server
{
	class ioc_register_command final : public i_command
	{
	public:
		ioc_register_command(std::string key,
			std::any function,
			std::shared_ptr<std::map<std::string, std::any>> container);

		void execute() override;

	private:
		std::string key_;
		std::any function_;
		std::shared_ptr<std::map<std::string, std::any>> container_;
	};
}
