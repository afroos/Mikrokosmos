module;

#include <memory>

#include <GLFW/glfw3.h>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Diagnostics.Logger;
import Mikrokosmos.Events.Event;
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

			void run();

			void onEvent(const Event& event);

		private:

			//bool onWindowClose(const WindowCloseEvent& event);

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
		_window = Window::create();
	}

	void Application::run()
	{
		mk::trace("Application starting.");
		while (_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->onUpdate();
		}
	}

	void Application::onEvent(const Event& event)
	{
		//mk::trace("{0}", event);
	}

	/*bool Application::onWindowClose(const WindowCloseEvent& event)
	{
		_running = false;
		return true;
	}*/

}