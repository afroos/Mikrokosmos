module;

#include <cassert>
#include <cstddef>
#include <ostream>

export module Mikrokosmos.Mathematics.Geometry.Point;

import Mikrokosmos.Mathematics.Algebra.Vector;

using Index = std::size_t;

export namespace mk
{
	template <std::size_t Dimension, typename Scalar>
	class Point
	{

	public:

		constexpr Point() = default;

		template<typename... CoordinateList> requires (sizeof...(CoordinateList) == Dimension)
			constexpr Point(CoordinateList&&... coordinates)
			: _coordinates(static_cast<Scalar>(coordinates)...)
		{
		}

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

		constexpr Vector<Dimension, Scalar> Coordinates() const { return _coordinates; }

		//auto operator<=>(const Point&) const = default;

	private:

		Vector<Dimension, Scalar> _coordinates{};
	};

	using Point2  = Point<2, double>;
	using Point2i = Point<2, int   >;
	using Point2f = Point<2, float >;
	using Point2d = Point<2, double>;

	using Point3  = Point<3, double>;
	using Point3i = Point<3, int   >;
	using Point3f = Point<3, float >;
	using Point3d = Point<3, double>;

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> operator-(const Point<Dimension, Scalar>& point1, const Point<Dimension, Scalar>& point2) noexcept
	{
		return (point1.Coordinates() - point2.Coordinates());
	}

	template <std::size_t Dimension, typename Scalar>
	std::ostream& operator<<(std::ostream& out, const Point<Dimension, Scalar>& point) noexcept
	{
		out << "{ ";

		for (Index index = 0; index < point.Size(); ++index)
		{
			out << std::showpos << std::scientific << point[index];
			if (index < point.Size() - 1) out << ", ";
		}

		out << " }";

		return out;
	}

}