#pragma once
#include <any>
#include <string>

namespace tank_battle_server
{
	class i_uobject
	{
	public:
		virtual std::any get_value(std::string const& key) = 0;
		virtual void set_value(std::string const& key, std::any const& value) = 0;

		virtual ~i_uobject() = default;
	};
}