module;

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Applications.LayerStack;
import Mikrokosmos.Events;
import Mikrokosmos.UI.Window;

export namespace mk
{
	class DebugLayer;

	class Application
	{

	public:

		MK_API Application();
		MK_API virtual ~Application();

		Application(const Application&)            = delete;
		Application(Application&&)                 = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&)      = delete;

		MK_API Window& Window() const;

		MK_API void Run();

		MK_API void OnEvent(Event& event);

		MK_API void PushLayer   (Layer* layer);
		MK_API void PushOverlay (Layer* layer);

		MK_API static Application& Get();

		mk::DebugLayer* DebugLayer();

	private:

		void OnWindowClosedEvent(WindowClosedEvent& event);
		void OnWindowResizedEvent(WindowResizedEvent& event);

	private:

		inline static Application* _instance { nullptr };

		std::unique_ptr<mk::Window> _window;

		LayerStack _layerStack;

		mk::DebugLayer* _debugLayer;

		bool _running   { true  };
		bool _minimized { false };

	};

}