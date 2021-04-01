module;

#include <sstream>
#include <string>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.WindowEvents;

import Mikrokosmos.Graphics.Extent2D;
import Mikrokosmos.Events.Event;

namespace mk
{

	export
	{

		class WindowClosedEvent : public Event
		{

		public:

			WindowClosedEvent() = default;

			std::string Name() const override;

		private:

		};


		class WindowResizedEvent : public Event
		{

		public:

			WindowResizedEvent(Extent2D newSize);

			std::string Name() const override;

			std::string ToString() const override;

			Extent2D NewSize() const;

		private:

			Extent2D _newSize;

		};

	}

}

module :private;

namespace mk
{

	std::string WindowClosedEvent::Name() const
	{
		return "Window Closed";
	}

	WindowResizedEvent::WindowResizedEvent(Extent2D newSize)
		: _newSize{ newSize }
	{
	}

	std::string WindowResizedEvent::Name() const
	{
		return "Window Resized";
	}

	std::string WindowResizedEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << NewSize();
		return stream.str();
	}

	Extent2D WindowResizedEvent::NewSize() const
	{
		return _newSize;
	}

}