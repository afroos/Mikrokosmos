module;

#include <sstream>
#include <string>
#include <type_traits>

export module Mikrokosmos.Events.KeyEvents;

import Mikrokosmos.Events.Event;
import Mikrokosmos.Input.Keyboard;

export namespace mk
{

	class KeyEvent : public Event
	{

	public:

		KeyEvent() = delete;

		Keyboard::Key Key() const;

	protected:

		KeyEvent(const Keyboard::Key key);

	private:

		Keyboard::Key _key;

	};

	class KeyPressedEvent : public KeyEvent
	{

	public:

		KeyPressedEvent() = delete;

		KeyPressedEvent(const Keyboard::Key key, std::size_t repeatCount);

		std::string Name()     const override;
		std::string ToString() const override;

	private:

		std::size_t _repeatCount;

	};

	class KeyReleasedEvent : public KeyEvent
	{

	public:

		KeyReleasedEvent() = delete;

		KeyReleasedEvent(const Keyboard::Key key);

		std::string Name()     const override;
		std::string ToString() const override;

	private:

	};

	class CharacterTypedEvent : public Event
	{

	public:

		CharacterTypedEvent(std::uint32_t character);

		std::string Name()     const override;
		std::string ToString() const override;

		std::uint32_t Character() const;

	private:

		std::uint32_t _character;

	};

}

module :private;

namespace mk
{

	Keyboard::Key KeyEvent::Key() const
	{
		return _key;
	}

	KeyEvent::KeyEvent(const Keyboard::Key key)
		: _key{ key }	
	{
	}

	KeyPressedEvent::KeyPressedEvent(const Keyboard::Key key, std::size_t repeatCount)
		: KeyEvent{ key },
		_repeatCount{ repeatCount }
	{
	}

	std::string KeyPressedEvent::Name() const
	{
		return "Key pressed";
	}

	std::string KeyPressedEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << static_cast<std::underlying_type<Keyboard::Key>::type>(Key());
		return stream.str();
	}

	KeyReleasedEvent::KeyReleasedEvent(const Keyboard::Key key)
		: KeyEvent{ key }
	{
	}

	std::string KeyReleasedEvent::Name() const
	{
		return "Key released";
	}

	std::string KeyReleasedEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << static_cast<std::underlying_type<Keyboard::Key>::type>(Key());
		return stream.str();
	}

	CharacterTypedEvent::CharacterTypedEvent(std::uint32_t character)
		: _character{ character }
	{
	}

	std::string CharacterTypedEvent::Name() const
	{
		return "Character typed";
	}

	std::string CharacterTypedEvent::ToString() const
	{
		std::stringstream stream;
		stream << Name() << ": " << Character();
		return stream.str();
	}

	std::uint32_t CharacterTypedEvent::Character() const
	{
		return _character;
	}

}