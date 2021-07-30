#pragma once
#include <any>
#include <functional>
#include <map>
#include <string>

#include "otus_homework/commands/ioc_register_command.hpp"

namespace tank_battle_server
{
	class ioc_container
	{
	public:
		ioc_container()
		{
			this->container_ = std::make_shared<std::map<std::string, std::any>>();
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> resolve(std::string const& ioc_key, std::string const& key, Args ...args)
		{
			if (ioc_key == std::string("ioc.register"))
			{
				return register_type<T>(key, args...);
			}

			throw std::runtime_error(ioc_key + " is undefined");
		}
		
		template <class T, typename ...Args>
		std::shared_ptr<T> resolve(std::string const& key, Args ...args)
		{
			//if (key == std::string("ioc.register"))
			//{
			//	return register_type<T>(args...);
			//}

			if (this->container_->find(key) == this->container_->end())
			{
				throw std::runtime_error("Dependency is not registered");
			}

			std::any function = this->container_->at(key);
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

		std::shared_ptr<std::map<std::string, std::any>> container_;
	};
}
