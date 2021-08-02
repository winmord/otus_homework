#pragma once

#include <string>
#include <map>
#include <any>
#include <stdexcept>
#include <memory>

namespace tank_battle_server
{
	class ioc_storage
	{
	public:
		bool is_scope_exists(std::shared_ptr<std::string> const& scope_id);
		bool is_dependency_exists(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name);
		void insert_scope(std::shared_ptr<std::string> const& scope_id);
		void insert_dependency(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name, std::any const& dep);
		void remove_dependency(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name);
		std::any get_dependency(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name);

	private:
		std::map<std::string, std::map<std::string, std::any>> container_;
	};
}
