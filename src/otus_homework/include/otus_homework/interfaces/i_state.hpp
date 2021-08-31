#pragma once

namespace tank_battle_server
{
	class i_state
	{
	public:
		virtual ~i_state() = default;
		virtual void to() = 0;
	};
}
