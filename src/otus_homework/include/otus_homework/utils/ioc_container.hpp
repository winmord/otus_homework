#pragma once
#include <any>
#include <functional>
#include <map>
#include <string>

#include "otus_homework/commands/ioc_checkout_scope_command.hpp"
#include "otus_homework/commands/ioc_new_scope_command.hpp"
#include "otus_homework/commands/ioc_register_command.hpp"
#include "otus_homework/commands/ioc_unregister_command.hpp"

namespace tank_battle_server
{
	class ioc_container
	{
	public:
		ioc_container()
		{
			this->current_scope_ = std::make_shared<std::string>("root");
			this->registered_scopes_ = std::make_shared<std::set<std::string>>();
			this->registered_scopes_->insert("root");
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> resolve(std::string const& ioc_key, std::string const& key, Args ...args)
		{
			if (ioc_key == std::string("ioc.register"))
			{
				return register_type<T>(key, args...);
			}

			if (ioc_key == std::string("ioc.unregister"))
			{
				return unregister_type<T>(key, args...);
			}

			if (ioc_key == std::string("scopes.current"))
			{
				return checkout_scope<T>(key);
			}

			if (ioc_key == std::string("scopes.new"))
			{
				return new_scope<T>(key);
			}

			throw std::runtime_error(ioc_key + " is undefined");
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> resolve(std::string const& key, Args ...args)
		{
			if (container_->find(key) == container_->end())
			{
				throw std::runtime_error("Dependency is not registered");
			}

			std::any function = container_->at(key);
			auto dependency = std::any_cast<std::function<std::shared_ptr<T>(Args ...)>>(function);

			return dependency(args...);
		}

	private:
		template <class T, typename ...Args>
		std::shared_ptr<T> register_type(Args ...args)
		{
			const auto arguments_count = sizeof...(args);
			if (arguments_count < 2)
				throw std::runtime_error("ioc.register must have 2 arguments at least: 1 - string, 2 - function");

			std::any arguments[arguments_count] = {args...};
			const auto key = std::any_cast<std::string>(arguments[0]);
			const auto function = arguments[1];

			return std::make_shared<ioc_register_command>(key, function, this->container_);
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> unregister_type(Args ...args)
		{
			const auto arguments_count = sizeof...(args);
			if (arguments_count < 1)
				throw std::runtime_error("ioc.unregister must have 1 arguments at least: 1 - string");

			std::any arguments[arguments_count] = {args...};
			const auto key = std::any_cast<std::string>(arguments[0]);

			return std::make_shared<ioc_unregister_command>(key, this->container_);
		}

		template <class T>
		std::shared_ptr<T> new_scope(std::string const& scope_id)
		{
			return std::make_shared<ioc_new_scope_command>(scope_id, this->registered_scopes_);
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> checkout_scope(Args ...args)
		{
			if (sizeof...(args) < 1)
				throw std::runtime_error(
					"scope.current must have 1 arguments at least: 1 - string");
			std::any checkout_arguments[sizeof...(args)] = {args...};

			const std::string scope_id = std::any_cast<std::string>(checkout_arguments[0]);

			if (this->registered_scopes_->find(scope_id) == this->registered_scopes_->end())
				throw std::runtime_error(
					"scope " + scope_id + " does not exist");

			return std::make_shared<ioc_checkout_scope_command>(scope_id, this->current_scope_);
		}

		inline thread_local static
		std::shared_ptr<std::map<std::string, std::any>> container_ =
			std::make_shared<std::map<std::string, std::any>>();

		std::shared_ptr<std::string> current_scope_;

		std::shared_ptr<std::set<std::string>> registered_scopes_;
	};
}
