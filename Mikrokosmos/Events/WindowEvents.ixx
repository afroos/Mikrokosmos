module;

#include <sstream>
#include <string>

export module Mikrokosmos.Events.WindowEvents;

import Mikrokosmos.Events.Event;
import Mikrokosmos.Mathematics.Algebra.Vector;

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

			WindowResizedEvent(const Vector2u& newSize);

			std::string Name()     const override;
			std::string ToString() const override;

			Vector2u NewSize() const;

		private:

			Vector2u _newSize;

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

	WindowResizedEvent::WindowResizedEvent(const Vector2u& newSize)
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

	Vector2u WindowResizedEvent::NewSize() const
	{
		return _newSize;
	}

}