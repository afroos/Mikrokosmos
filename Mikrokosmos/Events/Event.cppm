module;

//#include <memory>

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

			bool handled() const;

			void handled(bool value);

		private:

			bool _handled{ false };

		};

	}

}

module :private;

namespace mk
{

	bool Event::handled() const
	{
		return _handled;
	}

	void Event::handled(bool value)
	{
		_handled = value;
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