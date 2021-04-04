module;

#include <memory>

#include <Mikrokosmos/Core.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module Mikrokosmos.Platform.Win32.Window;

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

	constexpr Mouse::Button MapButton(int button)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_1:    return Mouse::Button::Left;
			case GLFW_MOUSE_BUTTON_2:    return Mouse::Button::Right;
			case GLFW_MOUSE_BUTTON_3:    return Mouse::Button::Middle;

			default:                     return Mouse::Button::Unknown;
		}
	}

	constexpr Keyboard::Key MapKey(int key)
	{
		switch (key)
		{
			case GLFW_KEY_SPACE:         return Keyboard::Key::Space;
			case GLFW_KEY_APOSTROPHE:    return Keyboard::Key::Quote;
			case GLFW_KEY_COMMA:         return Keyboard::Key::Comma;
			case GLFW_KEY_MINUS:         return Keyboard::Key::Hyphen;
			case GLFW_KEY_PERIOD:        return Keyboard::Key::Period;
			case GLFW_KEY_SLASH:         return Keyboard::Key::Slash;
			case GLFW_KEY_0:             return Keyboard::Key::Num0;
			case GLFW_KEY_1:             return Keyboard::Key::Num1;
			case GLFW_KEY_2:             return Keyboard::Key::Num2;
			case GLFW_KEY_3:             return Keyboard::Key::Num3;
			case GLFW_KEY_4:             return Keyboard::Key::Num4;
			case GLFW_KEY_5:             return Keyboard::Key::Num5;
			case GLFW_KEY_6:             return Keyboard::Key::Num6;
			case GLFW_KEY_7:             return Keyboard::Key::Num7;
			case GLFW_KEY_8:             return Keyboard::Key::Num8;
			case GLFW_KEY_9:             return Keyboard::Key::Num9;
			case GLFW_KEY_SEMICOLON:     return Keyboard::Key::Semicolon;
			case GLFW_KEY_EQUAL:         return Keyboard::Key::Equal;
			case GLFW_KEY_A:             return Keyboard::Key::A;
			case GLFW_KEY_B:             return Keyboard::Key::B;
			case GLFW_KEY_C:             return Keyboard::Key::C;
			case GLFW_KEY_D:             return Keyboard::Key::D;
			case GLFW_KEY_E:             return Keyboard::Key::E;
			case GLFW_KEY_F:             return Keyboard::Key::F;
			case GLFW_KEY_G:             return Keyboard::Key::G;
			case GLFW_KEY_H:             return Keyboard::Key::H;
			case GLFW_KEY_I:             return Keyboard::Key::I;
			case GLFW_KEY_J:             return Keyboard::Key::J;
			case GLFW_KEY_K:             return Keyboard::Key::K;
			case GLFW_KEY_L:             return Keyboard::Key::L;
			case GLFW_KEY_M:             return Keyboard::Key::M;
			case GLFW_KEY_N:             return Keyboard::Key::N;
			case GLFW_KEY_O:             return Keyboard::Key::O;
			case GLFW_KEY_P:             return Keyboard::Key::P;
			case GLFW_KEY_Q:             return Keyboard::Key::Q;
			case GLFW_KEY_R:             return Keyboard::Key::R;
			case GLFW_KEY_S:             return Keyboard::Key::S;
			case GLFW_KEY_T:             return Keyboard::Key::T;
			case GLFW_KEY_U:             return Keyboard::Key::U;
			case GLFW_KEY_V:             return Keyboard::Key::V;
			case GLFW_KEY_W:             return Keyboard::Key::W;
			case GLFW_KEY_X:             return Keyboard::Key::X;
			case GLFW_KEY_Y:             return Keyboard::Key::Y;
			case GLFW_KEY_Z:             return Keyboard::Key::Z;
			case GLFW_KEY_LEFT_BRACKET:  return Keyboard::Key::LBracket;
			case GLFW_KEY_BACKSLASH:     return Keyboard::Key::Backslash;
			case GLFW_KEY_RIGHT_BRACKET: return Keyboard::Key::RBracket;
			case GLFW_KEY_ESCAPE:        return Keyboard::Key::Escape;
			case GLFW_KEY_ENTER:         return Keyboard::Key::Enter;
			case GLFW_KEY_TAB:           return Keyboard::Key::Tab;
			case GLFW_KEY_BACKSPACE:     return Keyboard::Key::Backspace;
			case GLFW_KEY_INSERT:        return Keyboard::Key::Insert;
			case GLFW_KEY_DELETE:        return Keyboard::Key::Delete;
			case GLFW_KEY_RIGHT:         return Keyboard::Key::Right;
			case GLFW_KEY_LEFT:          return Keyboard::Key::Left;
			case GLFW_KEY_DOWN:          return Keyboard::Key::Down;
			case GLFW_KEY_UP:            return Keyboard::Key::Up;
			case GLFW_KEY_PAGE_UP:       return Keyboard::Key::PageUp;
			case GLFW_KEY_PAGE_DOWN:     return Keyboard::Key::PageDown;
			case GLFW_KEY_HOME:          return Keyboard::Key::Home;
			case GLFW_KEY_END:           return Keyboard::Key::End;
			case GLFW_KEY_PAUSE:         return Keyboard::Key::Pause;
			case GLFW_KEY_F1:            return Keyboard::Key::F1;
			case GLFW_KEY_F2:            return Keyboard::Key::F2;
			case GLFW_KEY_F3:            return Keyboard::Key::F3;
			case GLFW_KEY_F4:            return Keyboard::Key::F4;
			case GLFW_KEY_F5:            return Keyboard::Key::F5;
			case GLFW_KEY_F6:            return Keyboard::Key::F6;
			case GLFW_KEY_F7:            return Keyboard::Key::F7;
			case GLFW_KEY_F8:            return Keyboard::Key::F8;
			case GLFW_KEY_F9:            return Keyboard::Key::F9;
			case GLFW_KEY_F10:           return Keyboard::Key::F10;
			case GLFW_KEY_F11:           return Keyboard::Key::F11;
			case GLFW_KEY_F12:           return Keyboard::Key::F12;
			case GLFW_KEY_F13:           return Keyboard::Key::F13;
			case GLFW_KEY_F14:           return Keyboard::Key::F14;
			case GLFW_KEY_F15:           return Keyboard::Key::F15;
			case GLFW_KEY_KP_0:          return Keyboard::Key::Numpad0;
			case GLFW_KEY_KP_1:          return Keyboard::Key::Numpad1;
			case GLFW_KEY_KP_2:          return Keyboard::Key::Numpad2;
			case GLFW_KEY_KP_3:          return Keyboard::Key::Numpad3;
			case GLFW_KEY_KP_4:          return Keyboard::Key::Numpad4;
			case GLFW_KEY_KP_5:          return Keyboard::Key::Numpad5;
			case GLFW_KEY_KP_6:          return Keyboard::Key::Numpad6;
			case GLFW_KEY_KP_7:          return Keyboard::Key::Numpad7;
			case GLFW_KEY_KP_8:          return Keyboard::Key::Numpad8;
			case GLFW_KEY_KP_9:          return Keyboard::Key::Numpad9;
			case GLFW_KEY_KP_DECIMAL:    return Keyboard::Key::Period; // Decimal?
			case GLFW_KEY_KP_DIVIDE:     return Keyboard::Key::Divide;
			case GLFW_KEY_KP_MULTIPLY:   return Keyboard::Key::Multiply;
			case GLFW_KEY_KP_SUBTRACT:   return Keyboard::Key::Subtract;
			case GLFW_KEY_KP_ADD:        return Keyboard::Key::Add;
			case GLFW_KEY_KP_ENTER:      return Keyboard::Key::Enter;
			case GLFW_KEY_KP_EQUAL:      return Keyboard::Key::Equal;
			case GLFW_KEY_LEFT_SHIFT:    return Keyboard::Key::LShift;
			case GLFW_KEY_LEFT_CONTROL:  return Keyboard::Key::LControl;
			case GLFW_KEY_LEFT_ALT:      return Keyboard::Key::LAlt;
			case GLFW_KEY_LEFT_SUPER:    return Keyboard::Key::LSystem;
			case GLFW_KEY_RIGHT_SHIFT:   return Keyboard::Key::RShift;
			case GLFW_KEY_RIGHT_CONTROL: return Keyboard::Key::RControl;
			case GLFW_KEY_RIGHT_ALT:     return Keyboard::Key::RAlt;
			case GLFW_KEY_RIGHT_SUPER:   return Keyboard::Key::RSystem;
			case GLFW_KEY_MENU:          return Keyboard::Key::Menu;

			default:                     return Keyboard::Key::Unknown;
		}
	}

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

				auto newSize = Vector2u{ static_cast<std::size_t>(width), static_cast<std::size_t>(height) };

				WindowResizedEvent event{ newSize };

				data->callback(event);
			});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event{ MapKey(key), 0 };
					data->callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event{ MapKey(key) };
					data->callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event{ MapKey(key), 1 };
					data->callback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));

				CharacterTypedEvent event{ keycode };
				data->callback(event);
			});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event{ MapButton(button) };
						data->callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event{ MapButton(button) };
						data->callback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event{ Vector2i {static_cast<int>(xOffset), static_cast<int>(yOffset)} };
				
				data->callback(event);
			});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				auto data = static_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent event{ Point2i {static_cast<int>(xPos), static_cast<int>(yPos)} };
				
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