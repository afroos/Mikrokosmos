module;

#include <memory>

#include <Mikrokosmos/Core.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
		auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(_window, this);
		// VSync?

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));
							
				WindowClosedEvent event;

				data->callback(event);
			});

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));

				auto newSize = Extent2D{ static_cast<std::size_t>(width), 
					                     static_cast<std::size_t>(height) };

				WindowResizedEvent event{ newSize };

				data->callback(event);
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