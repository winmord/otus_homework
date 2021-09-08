#pragma once
#include <any>
#include <functional>
#include <string>

#include "otus_homework/utils/ioc_storage.hpp"
#include "otus_homework/commands/ioc_checkout_scope_command.hpp"
#include "otus_homework/commands/ioc_new_scope_command.hpp"
#include "otus_homework/commands/ioc_register_command.hpp"
#include "otus_homework/commands/ioc_unregister_command.hpp"
#include "otus_homework/commands/setup_tank_direction_command.hpp"
#include "otus_homework/commands/setup_tank_owner_command.hpp"
#include "otus_homework/commands/setup_tank_position_command.hpp"
#include "otus_homework/interfaces/i_uobject.hpp"

namespace tank_battle_server
{
	class ioc_container
	{
	public:
		ioc_container()
		{
			this->current_scope_ = std::make_shared<std::string>("root");
			this->container_->insert_scope(this->current_scope_);
			this->objects_count_ = std::make_shared<int>(0);
			this->player_1_object_position_ = std::make_shared<int>(0);
			this->player_2_object_position_ = std::make_shared<int>(0);
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
		std::shared_ptr<T> resolve(std::string const& key, std::shared_ptr<i_uobject> obj, Args ...args)
		{
			auto value = std::any_cast<T>(obj->get_value(key));
			return std::make_shared<T>(value);
		}

		template <>
		std::shared_ptr<i_command> resolve<i_command>(std::string const& key, std::shared_ptr<i_uobject> obj)
		{
			if (key == std::string("set tank direction"))
			{
				return std::make_shared<setup_tank_direction_command>(obj, 1);
			}
			if (key == std::string("set tank owner"))
			{
				return std::make_shared<setup_tank_owner_command>(obj, (*this->objects_count_)++ > 2 ? 1 : 0);
			}
			if (key == std::string("set tank position"))
			{
				const auto tanks_distance{5};
				const auto tank_owner = std::any_cast<int>(obj->get_value("owner"));
				const auto tank_position = movement_vector(
					{
						tank_owner ? (*this->player_2_object_position_)++ : (*this->player_1_object_position_)++,
						tank_owner ? tanks_distance : 0
					}
				);

				return std::make_shared<setup_tank_position_command>(obj, tank_position);
			}

			throw std::runtime_error(key + " is undefined");
		}

		template <typename ...Args>
		void resolve(std::string const& key, std::shared_ptr<i_uobject> obj, Args ...args)
		{
			const auto arguments_count = sizeof...(args);
			std::any arguments[arguments_count] = {args...};

			obj->set_value(key, arguments[0]);
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> resolve(std::string const& key, Args ...args)
		{
			if (key == std::string("object"))
			{
				return std::shared_ptr<T>();
			}

			if (key.find("tank.operations") != std::string::npos)
			{
				return nullptr;
			}

			if (!container_->is_dependency_exists(this->current_scope_, key))
			{
				throw std::runtime_error("Dependency is not registered");
			}

			std::any function = container_->get_dependency(this->current_scope_, key);

			try
			{
				auto dependency = std::any_cast<std::function<std::shared_ptr<T>(Args ...)>>(function);
				return dependency(args...);
			}
			catch (...)
			{
				throw std::runtime_error("can not cast dependency");
			}
		}

		~ioc_container()
		{
			container_.reset();
			current_scope_.reset();
		}

	private:
		template <class T, typename ...Args>
		std::shared_ptr<T> register_type(Args ...args)
		{
			const auto arguments_count = sizeof...(args);
			if (arguments_count < 2)
				throw std::runtime_error("ioc.register must have 2 arguments at least: 1 - string, 2 - function");

			std::any arguments[arguments_count] = {args...};

			std::string key;
			try
			{
				key = std::any_cast<std::string>(arguments[0]);
			}
			catch (...)
			{
				throw std::runtime_error("ioc.register can not cast dependency name argument");
			}

			const auto function = arguments[1];

			return std::make_shared<ioc_register_command>(key, function, this->current_scope_, this->container_);
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> unregister_type(Args ...args)
		{
			const auto arguments_count = sizeof...(args);
			if (arguments_count < 1)
				throw std::runtime_error("ioc.unregister must have 1 arguments at least: 1 - string");

			std::any arguments[arguments_count] = {args...};

			std::string key;
			try
			{
				key = std::any_cast<std::string>(arguments[0]);
			}
			catch (...)
			{
				throw std::runtime_error("ioc.unregister can not cast argument");
			}

			return std::make_shared<ioc_unregister_command>(key, this->current_scope_, this->container_);
		}

		template <class T>
		std::shared_ptr<T> new_scope(std::string const& scope_id)
		{
			return std::make_shared<ioc_new_scope_command>(std::make_shared<std::string>(scope_id), this->container_);
		}

		template <class T, typename ...Args>
		std::shared_ptr<T> checkout_scope(Args ...args)
		{
			if (sizeof...(args) < 1)
				throw std::runtime_error("scope.current must have 1 arguments at least: 1 - string");
			std::any checkout_arguments[sizeof...(args)] = {args...};

			std::string scope_id;
			try
			{
				scope_id = std::any_cast<std::string>(checkout_arguments[0]);
			}
			catch (...)
			{
				throw std::runtime_error("scope.current can not cast argument");
			}

			if (!this->container_->is_scope_exists(std::make_shared<std::string>(scope_id)))
				throw std::runtime_error("scope " + scope_id + " does not exist");

			return std::make_shared<ioc_checkout_scope_command>(scope_id,
			                                                    this->current_scope_,
			                                                    this->objects_count_,
			                                                    this->player_1_object_position_,
			                                                    this->player_2_object_position_);
		}

		thread_local static std::shared_ptr<ioc_storage> container_;
		std::shared_ptr<std::string> current_scope_;

		std::shared_ptr<int> objects_count_;
		std::shared_ptr<int> player_1_object_position_;
		std::shared_ptr<int> player_2_object_position_;
	};
}
