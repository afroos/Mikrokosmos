module;

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Layer;

export namespace mk
{

	class Application;
	class Event;

	class MK_API Layer
	{

	public:

		Layer(Application& application);
		~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& event);

	protected:

		Application& _application;

	};

}