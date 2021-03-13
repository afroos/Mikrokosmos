module;

#include <memory>

#include <GLFW/glfw3.h>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Platform.Win32.Window;

import Mikrokosmos.UI.Window;

namespace mk
{
	export
	{

		class Win32Window : public Window
		{

		public:

			Win32Window(const WindowDescription& description);

			virtual ~Win32Window();

			void OnUpdate() override;

		private:

			GLFWwindow* _window;

			/*struct WindowData
			{
				std::string title;
				unsigned int width, height;
				bool verticalSync;

				EventCallbackFn EventCallback;
			};

			WindowData _data;*/

		};

		std::unique_ptr<Window> Window::Create(const WindowDescription& description)
		{
			return std::make_unique<Win32Window>(description);
		}

	}
	
}

module :private;

namespace mk
{

	Win32Window::Win32Window(const WindowDescription& description)
		:
		Window(description)
	{
		glfwInit();

		_window = glfwCreateWindow(static_cast<int>(description.size.width), 
			                       static_cast<int>(description.size.height), 
			                       description.title.c_str(), 
			                       nullptr, 
			                       nullptr);

		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, this);
		// VSync?

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));
							
				data->closedEvent.Fire();
			});

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));

				auto newSize = Extent2D{ static_cast<std::size_t>(width), static_cast<std::size_t>(height) };

				data->resizedEvent.Fire(newSize);
			});

	}

	Win32Window::~Win32Window()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void Win32Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

}