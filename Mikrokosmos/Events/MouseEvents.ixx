module;

#include <string>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.MouseEvents;

import Mikrokosmos.Events.Event;

namespace mk
{

	export
	{

		class MouseMovedEvent : public Event
		{

		public:

			MouseMovedEvent() = default;

			std::string Name() const override;

		private:

		};

	}

}

module :private;

namespace mk
{

	std::string MouseMovedEvent::Name() const
	{
		return "Mouse Moved";
	}

}