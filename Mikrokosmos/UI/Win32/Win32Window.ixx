module;

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module Mikrokosmos.UI.Win32Window;

import Mikrokosmos.Events.KeyEvents;
import Mikrokosmos.Events.MouseEvents;
import Mikrokosmos.Events.WindowEvents;
import Mikrokosmos.Input.Keyboard;
import Mikrokosmos.Input.Mouse;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;
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

			void* NativeHandle() const;

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

		_window = glfwCreateWindow(static_cast<int>(Width()), 
			                       static_cast<int>(Height()), 
			                       description.title.c_str(), 
			                       nullptr, 
			                       nullptr);

		glfwSetWindowUserPointer(_window, this);
		// VSync?

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
			{
				auto data = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
							
				WindowClosedEvent event;

				data->EventCallback(event);
			});

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
			{
				auto data = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

				auto newSize = Vector2u{ static_cast<std::size_t>(width), static_cast<std::size_t>(height) };

				WindowResizedEvent event{ newSize };

				data->EventCallback(event);
			});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto data = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event{ ToMikrokosmosKey(key), 0 };
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event{ ToMikrokosmosKey(key) };
					data->EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event{ ToMikrokosmosKey(key), 1 };
					data->EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode)
			{
				auto data = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

				CharacterTypedEvent event{ keycode };
				data->EventCallback(event);
			});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto data = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event{ ToMikrokosmosButton(button) };
						data->EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event{ ToMikrokosmosButton(button) };
						data->EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto data = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event{ Vector2i {static_cast<int>(xOffset), static_cast<int>(yOffset)} };
				
				data->EventCallback(event);
			});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				auto data = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent event{ Point2i {static_cast<int>(xPos), static_cast<int>(yPos)} };
				
				data->EventCallback(event);
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
	}

	void* Win32Window::NativeHandle() const
	{
		return _window;
	}

}