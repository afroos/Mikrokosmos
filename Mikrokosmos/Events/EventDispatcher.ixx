module;

#include <functional>
#include <vector>

export module Mikrokosmos.Events.EventDispatcher;

import Mikrokosmos.Events.Event;
import Mikrokosmos.Events.Delegate;

namespace mk
{
	export
	{	

		class EventDispatcher
		{

		public:

			EventDispatcher(Event& event)
				:
				_event{ event }
			{
			}

			template<typename Object, typename EventType>
			using Method = void(Object::*)(EventType&);

			template <typename EventType, typename Object>
			bool Dispatch(Object* object, Method<Object, EventType> method)
			{
				if (_event.Is<EventType>())
				{
					using EventCallback = Delegate<void(EventType&)>;

					EventCallback callback;
					
					callback.Bind(object, method);
					
					callback(static_cast<EventType&>(_event));
					
					return true;
				}
				return false;
			}

		private:
			
			Event& _event;

		};

	}

}

module :private;

namespace mk
{


}