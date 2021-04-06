module;

#include <Mikrokosmos/Core.h>
#include <GLFW/glfw3.h> 

module Mikrokosmos.Input.Mouse;

import Mikrokosmos.Applications.Application;
import Mikrokosmos.Diagnostics.Logger;

#ifdef MK_PLATFORM_WIN32

namespace mk
{
	bool Mouse::IsButtonPressed(Button button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().Window().NativeHandle());
		auto state = glfwGetMouseButton(window, ToPlatformButton(button));
        return state == GLFW_PRESS;
	}

	Vector2i Mouse::Position()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().Window().NativeHandle());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return Vector2i{ static_cast<int>(x), static_cast<int>(y) };
	}

	constexpr Mouse::Button ToMikrokosmosButton(int platformButton)
	{
		Mouse::Button button;

		switch (platformButton)
		{
			case GLFW_MOUSE_BUTTON_1: button = Mouse::Button::Left;    break; 
			case GLFW_MOUSE_BUTTON_2: button = Mouse::Button::Right;   break;
			case GLFW_MOUSE_BUTTON_3: button = Mouse::Button::Middle;  break;

			default:                  button = Mouse::Button::Unknown; break;
		}

		return button;
	}

	constexpr int ToPlatformButton(Mouse::Button button)
	{
		int platformButton;

		switch (button)
		{
			case Mouse::Button::Left:   platformButton =  0; break;
			case Mouse::Button::Right:  platformButton =  1; break;
			case Mouse::Button::Middle: platformButton =  2; break;

			default:                    platformButton = -1; break;
		}

		return platformButton;
	}

}

#endif