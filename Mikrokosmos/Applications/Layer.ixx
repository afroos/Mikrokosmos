module;

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Layer;

import Mikrokosmos.Events.Event;

export namespace mk
{

	class MK_API Layer
	{

	public:

		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach()            {}
		virtual void OnDetach()            {}
		virtual void OnUpdate()            {}
		virtual void OnEvent(Event& event) {}
		virtual void OnRender()            {}

	};

}

module :private;

namespace mk
{

}