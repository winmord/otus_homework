#pragma once

#include <vector>
#include "otus_homework/otus_homework_api.hpp"

namespace OTUS_HOMEWORK_API tank_battle_server
{
	class  movement_vector
	{
	public:
		explicit movement_vector(std::vector<int> body);

		movement_vector operator+(movement_vector const& rhs) const;
		movement_vector operator+=(movement_vector const& rhs);
		bool operator==(movement_vector const& rhs) const;
		movement_vector rotate(const double angle) const;
	
	private:
		std::vector<int> body_;
	};
}
