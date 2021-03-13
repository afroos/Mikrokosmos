module;

#include <ostream>
#include <string>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.Event;

namespace mk
{

	export
	{

		class Event
		{

		public:

			virtual ~Event() = default;

			virtual std::string Name() const = 0;

			virtual std::string ToString() const;

		private:

			bool _handled{ false };

		};

		std::ostream& operator<<(std::ostream& output, const Event& event)
		{
			return output << "Event: " << event.ToString();
		}

	}

}

module :private;

namespace mk
{

	std::string Event::ToString() const
	{
		return Name();
	}

}


/*

Types
	AppTick
	AppUpdate
	AppRender
	WindowClose
	WindowResize
	WindowFocus
	WindowLostFocus
	WindowMoved
	KeyPressed
	KeyReleased
	KeyTyped
	MouseButtonPressed
	MouseButtonReleased
	MouseMoved
	MouseScrolled

Categories
	Application    
	Keyboard
	Mouse
	
Methods
	int type();
	std::string name();
	std::string description();
	int category();
	bool handled();

	
	
	
	
	
	
	
	
	
	*/