#pragma once

#include <vector>

namespace tank_battle_server
{
	class movement_vector
	{
	public:
		explicit movement_vector(std::vector<int> body);

		movement_vector operator+(movement_vector const& rhs) const;
		movement_vector operator+=(movement_vector const& rhs);
		bool operator==(movement_vector const& rhs) const;
	
	private:
		std::vector<int> body_;
	};
}
