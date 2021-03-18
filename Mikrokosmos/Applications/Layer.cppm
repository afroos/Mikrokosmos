module;

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Layer;

import Mikrokosmos.Events.Event;

namespace mk
{
	export
	{

		class MK_API Layer
		{

		public:

			Layer()  = default;
			~Layer() = default;

			virtual void OnAttach ()                {}
			virtual void OnDetach ()                {}
			virtual void OnUpdate (float  timeStep) {}
			virtual void OnEvent  (Event& event)    {}

		private:

		};

	}
	
}

module : private;

namespace mk
{
	
}