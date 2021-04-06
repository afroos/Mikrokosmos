module;

#include <array>
#include <cassert>
#include <cmath>
#include <ostream>

export module Mikrokosmos.Mathematics.Algebra.Vector;

using Index = std::size_t;

export namespace mk
{
	template <std::size_t Dimension, typename Scalar>
	class Vector
	{
	public:

		constexpr Vector() = default;

		template<typename... CoordinateList> requires (sizeof...(CoordinateList) == Dimension)
			constexpr Vector(CoordinateList&&... coordinates) noexcept
			: _coordinates{ static_cast<Scalar>(coordinates)... }
		{
		}

		constexpr Vector(const Vector<3, Scalar>& vector, Scalar w) requires (Dimension == 4)
			: _coordinates{ vector[0], vector[1], vector[2], w }
		{
		}

		constexpr Vector(Vector<Dimension + 1, Scalar> other) noexcept
		{
			for (Index index = 0; index < Size(); ++index)
			{
				_coordinates[index] = other[index];
			}
		}

		static constexpr Vector Zero() noexcept { return Vector(); }

		constexpr const Scalar& operator[](Index index) const
		{
			assert(index < Size());
			return _coordinates[index];
		}

		constexpr Scalar& operator[](Index index)
		{
			assert(index < Size());
			return _coordinates[index];
		}

		constexpr std::size_t Size() const noexcept { return Dimension; }

		constexpr       Scalar& X()       requires (Dimension > 0) { return _coordinates[0]; }
		constexpr const Scalar& X() const requires (Dimension > 0) { return _coordinates[0]; }

		constexpr       Scalar& Y()       requires (Dimension > 1) { return _coordinates[1]; }
		constexpr const Scalar& Y() const requires (Dimension > 1) { return _coordinates[1]; }
		
		constexpr       Scalar& Z()       requires (Dimension > 2) { return _coordinates[2]; }
		constexpr const Scalar& Z() const requires (Dimension > 2) { return _coordinates[2]; }

		constexpr       Scalar& w()       requires (Dimension > 3) { return _coordinates[3]; }
		constexpr const Scalar& w() const requires (Dimension > 3) { return _coordinates[3]; }

		constexpr Vector& operator+=(const Vector& other) noexcept
		{
			for (Index index = 0; index < Size(); ++index)
			{
				_coordinates[index] += other[index];
			}
			return *this;
		}

		constexpr Vector& operator-=(const Vector& other) noexcept
		{
			for (Index index = 0; index < Size(); ++index)
			{
				_coordinates[index] -= other[index];
			}
			return *this;
		}

		constexpr Vector& operator*=(const Scalar scalar) noexcept
		{
			for (Index index = 0; index < Size(); ++index)
			{
				_coordinates[index] *= scalar;
			}
			return *this;
		}

		constexpr Vector& operator/=(const Scalar scalar) noexcept
		{
			auto inverseScalar = Scalar{ 1 } / scalar;

			*this *= inverseScalar;

			return *this;
		}

		auto operator<=>(const Vector&) const = default;

	private:
		std::array<Scalar, Dimension> _coordinates{ };
	};

	using Vector2  = Vector<2, double      >;
	using Vector2u = Vector<2, unsigned int>;
	using Vector2i = Vector<2, int         >;
	using Vector2f = Vector<2, float       >;
	using Vector2d = Vector<2, double      >;

	using Vector3  = Vector<3, double      >;
	using Vector3u = Vector<3, unsigned int>;
	using Vector3i = Vector<3, int         >;
	using Vector3f = Vector<3, float       >;
	using Vector3d = Vector<3, double      >;

	using Vector4  = Vector<4, double      >;
	using Vector4u = Vector<4, unsigned int>;
	using Vector4i = Vector<4, int         >;
	using Vector4f = Vector<4, float       >;
	using Vector4d = Vector<4, double      >;

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> operator+(const Vector<Dimension, Scalar>& vector1, const Vector<Dimension, Scalar>& vector2) noexcept
	{
		Vector<Dimension, Scalar> result{ vector1 };
		result += vector2;
		return result;
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> operator-(const Vector<Dimension, Scalar>& vector1, const Vector<Dimension, Scalar>& vector2) noexcept
	{
		Vector<Dimension, Scalar> result{ vector1 };
		result -= vector2;
		return result;
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> operator*(Scalar scalar, const Vector<Dimension, Scalar>& vector) noexcept
	{
		Vector<Dimension, Scalar> result{ vector };
		result *= scalar;
		return result;
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> operator*(const Vector<Dimension, Scalar>& vector, Scalar scalar) noexcept
	{
		return scalar * vector;
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> operator/(const Vector<Dimension, Scalar>& vector, Scalar scalar) noexcept
	{
		Vector<Dimension, Scalar> result{ vector };
		result /= scalar;
		return result;
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Scalar dot(const Vector<Dimension, Scalar>& vector1, const Vector<Dimension, Scalar>& vector2) noexcept
	{
		auto result = Scalar{ 0 };
		for (Index i = 0; i < vector1.Size(); ++i)
		{
			result += vector1[i] * vector2[i];
		}
		return result;
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Scalar LengthSquared(const Vector<Dimension, Scalar>& vector) noexcept
	{
		return Dot(vector, vector);
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Scalar Length(const Vector<Dimension, Scalar>& vector) noexcept
	{
		return (float)std::sqrt((double)LengthSquared(vector));
	}

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> Normalize(const Vector<Dimension, Scalar>& vector) noexcept
	{
		Scalar length2 = Length(vector);

		if (length2 != 0.0f) return (vector / length2);
		else return Vector<Dimension, Scalar>::Zero();
	}

	template <typename Scalar>
	constexpr Vector<3, Scalar> Cross(const Vector<3, Scalar>& vector1, const Vector<3, Scalar>& vector2) noexcept
	{
		Vector<3, Scalar> result;

		result.X() = vector1.Y() * vector2.Z() - vector1.Z() * vector2.Y();
		result.Y() = vector1.Z() * vector2.X() - vector1.X() * vector2.Z();
		result.Z() = vector1.X() * vector2.Y() - vector1.Y() * vector2.X();

		return result;
	}

	template <std::size_t Dimension, typename Scalar>
	std::ostream& operator<<(std::ostream& out, const Vector<Dimension, Scalar>& vector) noexcept
	{
		out << "{ ";

		for (Index index = 0; index < vector.Size(); ++index)
		{
			out << std::showpos << std::scientific << vector[index];
			if (index < vector.Size() - 1) out << ", ";
		}

		out << " }";

		return out;
	}

	//Vector2f dummy;

}