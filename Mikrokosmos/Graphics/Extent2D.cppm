module;

#include <cstddef>
#include <ostream>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Graphics.Extent2D;

namespace mk
{
	export
	{

		struct Extent2D
		{
			std::size_t width;
			std::size_t height;

			auto operator<=>(const Extent2D&) const = default;
		};

		std::ostream& operator<<(std::ostream& output, const Extent2D& extent2D)
		{
			return output << "{" << extent2D.width << ", " << extent2D.height << "}";
		}

	}
	
}

module :private;

namespace mk
{
		
}