#include <utility>

#include "otus_homework/movement_vector.hpp"

#include <stdexcept>
#include <string>

namespace tank_battle_server
{
	movement_vector::movement_vector(std::vector<int> body)
		: body_(std::move(body))
	{
	}

	movement_vector movement_vector::operator+(movement_vector const& rhs) const
	{
		const auto body_size = this->body_.size();
		std::vector<int> vectors_sum_body(body_size, 0);

		for (auto coordinate_number = 0u; coordinate_number < body_size; ++coordinate_number)
		{
			vectors_sum_body[coordinate_number] = this->body_[coordinate_number] + rhs.body_[coordinate_number];
		}

		return movement_vector(vectors_sum_body);
	}

	movement_vector movement_vector::operator+=(movement_vector const& rhs)
	{
		return *this = *this + rhs;
	}

	bool movement_vector::operator==(movement_vector const& rhs) const
	{
		const auto body_size = this->body_.size();

		for (auto coordinate_number = 0u; coordinate_number < body_size; ++coordinate_number)
		{
			if (this->body_[coordinate_number] != rhs.body_[coordinate_number]) return false;
		}

		return true;
	}

	movement_vector movement_vector::rotate(const double angle) const
	{
		const auto body_size = this->body_.size();
		std::vector<int> rotated_vector(body_size);

		switch (body_size)
		{
		case 1:
			{
				
				rotated_vector[0] = static_cast<int>(round(this->body_[0] * cos(angle)));
				break;
			}
		case 2:
			{
				rotated_vector[0] = static_cast<int>(round(this->body_[0] * cos(angle) - this->body_[1] * sin(angle)));
				rotated_vector[1] = static_cast<int>(round(this->body_[0] * sin(angle) + this->body_[1] * cos(angle)));
				break;
			}
		default:
			{
				throw std::runtime_error("Rotation for " + std::to_string(body_size) + " dimensions not implemented yet.");
			}
		}

		return movement_vector(rotated_vector);
	}
}
