module;

#include <memory>

#include <GLFW/glfw3.h>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Platform.Win32.Window;

import Mikrokosmos.UI.Window;

export namespace mk
{

	class Win32Window : public Window
	{

	public:

		Win32Window(const WindowDescription& description);
		
		virtual ~Win32Window();

		void onUpdate() override;

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

	std::unique_ptr<Window> Window::create(const WindowDescription& description)
	{
		return std::make_unique<Win32Window>(description);
	}

}

module :private;

namespace mk
{

	Win32Window::Win32Window(const WindowDescription& description)
	{
		glfwInit();
		_window = glfwCreateWindow((int) description.size.width, (int) description.size.height, description.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_window);
	}

	Win32Window::~Win32Window()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void Win32Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

}