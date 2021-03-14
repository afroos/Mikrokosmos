module;

#include <memory>

#include <GLFW/glfw3.h>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Diagnostics.Logger;
import Mikrokosmos.Events;
import Mikrokosmos.UI.Window;

namespace mk
{
	export
	{

		class MK_API Application
		{

		public:

			Application();
			virtual ~Application() = default;

			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;

			void Run();

			void OnEvent(Event& event);

		private:

			void OnWindowClosed  (WindowClosedEvent&  event);
			void OnWindowResized (WindowResizedEvent& event);

			std::unique_ptr<Window> _window;

			bool _running   { true  };
			bool _minimized { false };

		};

	}
	
}

module : private;

namespace mk
{
	Application::Application()
	{
		_window = Window::Create();
		_window->callback.Bind(this, &Application::OnEvent);
	}

	void Application::Run()
	{
		mk::trace("Application started.");

		while (_running)
		{
			if (!_minimized)
			{
			}

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher{ event };

		dispatcher.Dispatch<WindowClosedEvent >(this, &Application::OnWindowClosed);
		dispatcher.Dispatch<WindowResizedEvent>(this, &Application::OnWindowResized);

		mk::trace("{0}", event);
	}

	void Application::OnWindowClosed(WindowClosedEvent& event)
	{
		_running = false;
		event.Handled(true);
	}

	void Application::OnWindowResized(WindowResizedEvent& event)
	{
		_minimized = (event.NewSize() == mk::Extent2D{0, 0});
		event.Handled(true);
	}

}