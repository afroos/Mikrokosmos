module;

#include <sstream>
#include <string>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.MouseEvents;

import Mikrokosmos.Events.Event;

export namespace mk
{

	class MouseButtonEvent : public Event
	{

	public:

		MouseButtonEvent() = default;

		std::string Name() const override;

	private:

	};

	class MouseButtonPressedEvent : public Event
	{

	public:

		MouseButtonPressedEvent() = default;

		std::string Name() const override;

	private:

	};

	class MouseButtonReleasedEvent : public Event
	{

	public:

		MouseButtonReleasedEvent() = default;

		std::string Name() const override;

	private:

	};

	class MouseMovedEvent : public Event
	{

	public:

		MouseMovedEvent() = default;

		std::string Name()     const override;
		std::string ToString() const override;

	private:

	};

	class MouseScrolledEvent : public Event
	{

	public:

		MouseScrolledEvent() = default;

		std::string Name()     const override;
		//std::string ToString() const override;

	private:

	};

}

module :private;

namespace mk
{

	std::string MouseButtonPressedEvent::Name() const
	{
		return "Mouse button pressed";
	}

	std::string MouseButtonReleasedEvent::Name() const
	{
		return "Mouse button released";
	}

	std::string MouseMovedEvent::Name() const
	{
		return "Mouse moved";
	}

	std::string MouseMovedEvent::ToString() const
	{
		std::stringstream stream;
		//stream << Name() << ": " << NewPosition();
		return stream.str();
	}

	std::string MouseScrolledEvent::Name() const
	{
		return "Mouse scrolled";
	}



}