#pragma once

namespace tank_battle_server
{
	class i_command
	{
	public:
		virtual void execute() = 0;
		
		virtual ~i_command() = default;
	};
}
