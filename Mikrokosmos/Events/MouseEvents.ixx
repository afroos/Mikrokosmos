module;

#include <sstream>
#include <string>
#include <type_traits>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.MouseEvents;

import Mikrokosmos.Events.Event;
import Mikrokosmos.Input.Mouse;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{

	class MouseButtonEvent : public Event
	{

	public:

		Mouse::Button Button() const;

	protected:

		MouseButtonEvent(const Mouse::Button button);

	private:

		Mouse::Button _button;

	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{

	public:

		MouseButtonPressedEvent(const Mouse::Button button);

		std::string Name()     const override;
		std::string ToString() const override;

	private:



	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{

	public:

		MouseButtonReleasedEvent(const Mouse::Button button);

		std::string Name()     const override;
		std::string ToString() const override;

	private:

	};

	class MouseMovedEvent : public Event
	{

	public:

		MouseMovedEvent(const Point2i newPosition);

		std::string Name()     const override;
		std::string ToString() const override;

		Point2i NewPosition() const;

	private:

		Point2i _newPosition;

	};

	class MouseScrolledEvent : public Event
	{

	public:

		MouseScrolledEvent(Vector2i offset);

		std::string Name()     const override;
		std::string ToString() const override;

		Vector2i Offset() const;

	private:

		Vector2i _offset;

	};

}

module :private;

namespace mk
{

	Mouse::Button MouseButtonEvent::Button() const
	{
		return _button;
	}

	MouseButtonEvent::MouseButtonEvent(const Mouse::Button button)
		: _button{ button }
	{
	}

	MouseButtonPressedEvent::MouseButtonPressedEvent(const Mouse::Button button)
		: MouseButtonEvent{ button }
	{
	}

	std::string MouseButtonPressedEvent::Name() const
	{
		return "Mouse button pressed";
	}

	std::string MouseButtonPressedEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << static_cast<std::underlying_type<Mouse::Button>::type>(Button());
		return stream.str();
	}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(const Mouse::Button button)
		: MouseButtonEvent{ button }
	{
	}

	std::string MouseButtonReleasedEvent::Name() const
	{
		return "Mouse button released";
	}

	std::string MouseButtonReleasedEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << static_cast<std::underlying_type<Mouse::Button>::type>(Button());
		return stream.str();
	}

	MouseMovedEvent::MouseMovedEvent(const Point2i newPosition)
		: _newPosition{ newPosition }
	{
	}

	std::string MouseMovedEvent::Name() const
	{
		return "Mouse moved";
	}

	std::string MouseMovedEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << NewPosition();
		return stream.str();
	}

	Point2i MouseMovedEvent::NewPosition() const
	{
		return _newPosition;
	}

	MouseScrolledEvent::MouseScrolledEvent(Vector2i offset)
		: _offset{ offset }
	{
	}

	std::string MouseScrolledEvent::Name() const
	{
		return "Mouse scrolled";
	}

	std::string MouseScrolledEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << Offset();
		return stream.str();
	}

	Vector2i MouseScrolledEvent::Offset() const
	{
		return _offset;
	}

}