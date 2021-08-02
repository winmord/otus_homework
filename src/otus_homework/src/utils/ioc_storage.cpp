#include "otus_homework/utils/ioc_storage.hpp"

namespace tank_battle_server
{
	bool ioc_storage::is_scope_exists(std::shared_ptr<std::string> const& scope_id)
	{
		return this->container_.find(*scope_id) != this->container_.end();
	}

	bool ioc_storage::is_dependency_exists(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name)
	{
		const auto scope_storage = this->container_.at(*scope_id);
		return scope_storage.find(dep_name) != scope_storage.end();
	}

	void ioc_storage::insert_scope(std::shared_ptr<std::string> const& scope_id)
	{
		this->container_.emplace(*scope_id, std::map<std::string, std::any>());
	}

	void ioc_storage::insert_dependency(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name, std::any const& dep)
	{
		this->container_.at(*scope_id).emplace(dep_name, dep);
	}

	void ioc_storage::remove_dependency(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name)
	{
		this->container_.at(*scope_id).erase(dep_name);
	}

	std::any ioc_storage::get_dependency(std::shared_ptr<std::string> const& scope_id, std::string const& dep_name)
	{
		return this->container_.at(*scope_id).at(dep_name);
	}
}
