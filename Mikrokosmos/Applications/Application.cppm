module;

#include <memory>

#include <GLFW/glfw3.h>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Diagnostics.Logger;
import Mikrokosmos.UI.Window;

export namespace mk
{
	class MK_EXPORT Application
	{

	public:

		Application();
		virtual ~Application() = default;

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void run()
		{
			mk::trace("Application starting.");
			while (true)
			{
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				_window->onUpdate();
			}
		}

	private:

		std::unique_ptr<Window> _window;

	};

}

module :private;

namespace mk
{
	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create(WindowDescription{}));
	}
}


