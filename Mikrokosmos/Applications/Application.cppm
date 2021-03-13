module;

#include <memory>

#include <GLFW/glfw3.h>

#include <Mikrokosmos/Core.h>

#include <typeindex> // Tirar.

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

		private:

			void OnWindowClosed(const WindowClosedEvent& event)
			{
				mk::trace("{0}", event);
				_running = false;
			}

			void OnWindowResized(const WindowResizedEvent& event)
			{
				mk::trace("{0}", event);
			}

			std::unique_ptr<Window> _window;

			bool _running { true };

		};

	}
	
}

module : private;

namespace mk
{
	Application::Application()
	{
		_window = Window::Create();
		_window->closedEvent.AddListener(this, &Application::OnWindowClosed);
		_window->resizedEvent.AddListener(this, &Application::OnWindowResized);

	}

	void Application::Run()
	{
		mk::trace("Application started.");

		while (_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->OnUpdate();
		}
	}

}