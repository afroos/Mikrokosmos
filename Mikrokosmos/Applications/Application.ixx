module;

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Applications.LayerStack;
import Mikrokosmos.Events;
import Mikrokosmos.UI.Window;

export namespace mk
{

	class Application
	{

	public:

		MK_API Application();
		MK_API virtual ~Application();

		Application(const Application&)            = delete;
		Application& operator=(const Application&) = delete;

		MK_API Window& Window() const;

		MK_API void Run();

		MK_API void OnEvent(Event& event);

		MK_API void PushLayer   (Layer* layer);
		MK_API void PushOverlay (Layer* layer);

	private:

		std::unique_ptr<mk::Window> _window;

		void OnWindowClosed  (WindowClosedEvent&  event);
		void OnWindowResized (WindowResizedEvent& event);

		LayerStack _layerStack;

		bool _running   { true  };
		bool _minimized { false };

	};

}