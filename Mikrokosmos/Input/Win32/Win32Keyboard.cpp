module;

#include <Mikrokosmos/Core.h>
#include <GLFW/glfw3.h> 

module Mikrokosmos.Input.Keyboard;

import Mikrokosmos.Applications.Application;
import Mikrokosmos.Diagnostics.Logger;

#ifdef MK_PLATFORM_WIN32

namespace mk
{
	bool Keyboard::IsKeyPressed(Key key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().Window().NativeHandle());
		auto state = glfwGetKey(window, ToPlatformKey(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	constexpr Keyboard::Key ToMikrokosmosKey(int platformKey)
	{
		Keyboard::Key key;

		switch (platformKey)
		{
			case GLFW_KEY_SPACE:         key = Keyboard::Key::Space;      break;
			case GLFW_KEY_APOSTROPHE:    key = Keyboard::Key::Apostrophe; break;
			case GLFW_KEY_COMMA:         key = Keyboard::Key::Comma;	  break;
			case GLFW_KEY_MINUS:         key = Keyboard::Key::Hyphen;	  break;
			case GLFW_KEY_PERIOD:        key = Keyboard::Key::Period;	  break;
			case GLFW_KEY_SLASH:         key = Keyboard::Key::Slash;	  break;
			case GLFW_KEY_0:             key = Keyboard::Key::Num0;		  break;
			case GLFW_KEY_1:             key = Keyboard::Key::Num1;		  break;
			case GLFW_KEY_2:             key = Keyboard::Key::Num2;		  break;
			case GLFW_KEY_3:             key = Keyboard::Key::Num3;		  break;
			case GLFW_KEY_4:             key = Keyboard::Key::Num4;		  break;
			case GLFW_KEY_5:             key = Keyboard::Key::Num5;		  break;
			case GLFW_KEY_6:             key = Keyboard::Key::Num6;		  break;
			case GLFW_KEY_7:             key = Keyboard::Key::Num7;		  break;
			case GLFW_KEY_8:             key = Keyboard::Key::Num8;		  break;
			case GLFW_KEY_9:             key = Keyboard::Key::Num9;		  break;
			case GLFW_KEY_SEMICOLON:     key = Keyboard::Key::Semicolon;  break;
			case GLFW_KEY_EQUAL:         key = Keyboard::Key::Equal;	  break;
			case GLFW_KEY_A:             key = Keyboard::Key::A;		  break;
			case GLFW_KEY_B:             key = Keyboard::Key::B;		  break;
			case GLFW_KEY_C:             key = Keyboard::Key::C;		  break;
			case GLFW_KEY_D:             key = Keyboard::Key::D;		  break;
			case GLFW_KEY_E:             key = Keyboard::Key::E;		  break;
			case GLFW_KEY_F:             key = Keyboard::Key::F;		  break;
			case GLFW_KEY_G:             key = Keyboard::Key::G;		  break;
			case GLFW_KEY_H:             key = Keyboard::Key::H;		  break;
			case GLFW_KEY_I:             key = Keyboard::Key::I;		  break;
			case GLFW_KEY_J:             key = Keyboard::Key::J;		  break;
			case GLFW_KEY_K:             key = Keyboard::Key::K;		  break;
			case GLFW_KEY_L:             key = Keyboard::Key::L;		  break;
			case GLFW_KEY_M:             key = Keyboard::Key::M;		  break;
			case GLFW_KEY_N:             key = Keyboard::Key::N;		  break;
			case GLFW_KEY_O:             key = Keyboard::Key::O;		  break;
			case GLFW_KEY_P:             key = Keyboard::Key::P;		  break;
			case GLFW_KEY_Q:             key = Keyboard::Key::Q;		  break;
			case GLFW_KEY_R:             key = Keyboard::Key::R;		  break;
			case GLFW_KEY_S:             key = Keyboard::Key::S;		  break;
			case GLFW_KEY_T:             key = Keyboard::Key::T;		  break;
			case GLFW_KEY_U:             key = Keyboard::Key::U;		  break;
			case GLFW_KEY_V:             key = Keyboard::Key::V;		  break;
			case GLFW_KEY_W:             key = Keyboard::Key::W;		  break;
			case GLFW_KEY_X:             key = Keyboard::Key::X;		  break;
			case GLFW_KEY_Y:             key = Keyboard::Key::Y;		  break;
			case GLFW_KEY_Z:             key = Keyboard::Key::Z;		  break;
			case GLFW_KEY_LEFT_BRACKET:  key = Keyboard::Key::LBracket;	  break;
			case GLFW_KEY_BACKSLASH:     key = Keyboard::Key::Backslash;  break;
			case GLFW_KEY_RIGHT_BRACKET: key = Keyboard::Key::RBracket;	  break;
			case GLFW_KEY_ESCAPE:        key = Keyboard::Key::Escape;	  break;
			case GLFW_KEY_ENTER:         key = Keyboard::Key::Enter;	  break;
			case GLFW_KEY_TAB:           key = Keyboard::Key::Tab;		  break;
			case GLFW_KEY_BACKSPACE:     key = Keyboard::Key::Backspace;  break;
			case GLFW_KEY_INSERT:        key = Keyboard::Key::Insert;	  break;
			case GLFW_KEY_DELETE:        key = Keyboard::Key::Delete;	  break;
			case GLFW_KEY_RIGHT:         key = Keyboard::Key::Right;	  break;
			case GLFW_KEY_LEFT:          key = Keyboard::Key::Left;		  break;
			case GLFW_KEY_DOWN:          key = Keyboard::Key::Down;		  break;
			case GLFW_KEY_UP:            key = Keyboard::Key::Up;		  break;
			case GLFW_KEY_PAGE_UP:       key = Keyboard::Key::PageUp;	  break;
			case GLFW_KEY_PAGE_DOWN:     key = Keyboard::Key::PageDown;	  break;
			case GLFW_KEY_HOME:          key = Keyboard::Key::Home;		  break;
			case GLFW_KEY_END:           key = Keyboard::Key::End;		  break;
			case GLFW_KEY_PAUSE:         key = Keyboard::Key::Pause;	  break;
			case GLFW_KEY_F1:            key = Keyboard::Key::F1;		  break;
			case GLFW_KEY_F2:            key = Keyboard::Key::F2;		  break;
			case GLFW_KEY_F3:            key = Keyboard::Key::F3;		  break;
			case GLFW_KEY_F4:            key = Keyboard::Key::F4;		  break;
			case GLFW_KEY_F5:            key = Keyboard::Key::F5;		  break;
			case GLFW_KEY_F6:            key = Keyboard::Key::F6;		  break;
			case GLFW_KEY_F7:            key = Keyboard::Key::F7;		  break;
			case GLFW_KEY_F8:            key = Keyboard::Key::F8;		  break;
			case GLFW_KEY_F9:            key = Keyboard::Key::F9;		  break;
			case GLFW_KEY_F10:           key = Keyboard::Key::F10;		  break;
			case GLFW_KEY_F11:           key = Keyboard::Key::F11;		  break;
			case GLFW_KEY_F12:           key = Keyboard::Key::F12;		  break;
			case GLFW_KEY_F13:           key = Keyboard::Key::F13;		  break;
			case GLFW_KEY_F14:           key = Keyboard::Key::F14;		  break;
			case GLFW_KEY_F15:           key = Keyboard::Key::F15;		  break;
			case GLFW_KEY_KP_0:          key = Keyboard::Key::Numpad0;	  break;
			case GLFW_KEY_KP_1:          key = Keyboard::Key::Numpad1;	  break;
			case GLFW_KEY_KP_2:          key = Keyboard::Key::Numpad2;	  break;
			case GLFW_KEY_KP_3:          key = Keyboard::Key::Numpad3;	  break;
			case GLFW_KEY_KP_4:          key = Keyboard::Key::Numpad4;	  break;
			case GLFW_KEY_KP_5:          key = Keyboard::Key::Numpad5;	  break;
			case GLFW_KEY_KP_6:          key = Keyboard::Key::Numpad6;	  break;
			case GLFW_KEY_KP_7:          key = Keyboard::Key::Numpad7;	  break;
			case GLFW_KEY_KP_8:          key = Keyboard::Key::Numpad8;	  break;
			case GLFW_KEY_KP_9:          key = Keyboard::Key::Numpad9;	  break;
			case GLFW_KEY_KP_DECIMAL:    key = Keyboard::Key::Period;     break; // Decimal?
			case GLFW_KEY_KP_DIVIDE:     key = Keyboard::Key::Divide;	  break;
			case GLFW_KEY_KP_MULTIPLY:   key = Keyboard::Key::Multiply;	  break;
			case GLFW_KEY_KP_SUBTRACT:   key = Keyboard::Key::Subtract;	  break;
			case GLFW_KEY_KP_ADD:        key = Keyboard::Key::Add;		  break;
			case GLFW_KEY_KP_ENTER:      key = Keyboard::Key::Enter;	  break;
			case GLFW_KEY_KP_EQUAL:      key = Keyboard::Key::Equal;	  break;
			case GLFW_KEY_LEFT_SHIFT:    key = Keyboard::Key::LShift;	  break;
			case GLFW_KEY_LEFT_CONTROL:  key = Keyboard::Key::LControl;	  break;
			case GLFW_KEY_LEFT_ALT:      key = Keyboard::Key::LAlt;		  break;
			case GLFW_KEY_LEFT_SUPER:    key = Keyboard::Key::LSystem;	  break;
			case GLFW_KEY_RIGHT_SHIFT:   key = Keyboard::Key::RShift;	  break;
			case GLFW_KEY_RIGHT_CONTROL: key = Keyboard::Key::RControl;	  break;
			case GLFW_KEY_RIGHT_ALT:     key = Keyboard::Key::RAlt;		  break;
			case GLFW_KEY_RIGHT_SUPER:   key = Keyboard::Key::RSystem;	  break;
			case GLFW_KEY_MENU:          key = Keyboard::Key::Menu;		  break;

			default:                     key = Keyboard::Key::Unknown;	  break;
		}

		return key;
	}

	constexpr int ToPlatformKey(Keyboard::Key key)
	{
		int platformKey;

		switch (key)
		{
			case Keyboard::Key::Space:      platformKey = GLFW_KEY_SPACE;          break;
			case Keyboard::Key::Apostrophe: platformKey = GLFW_KEY_APOSTROPHE;	   break;
			case Keyboard::Key::Comma:      platformKey = GLFW_KEY_COMMA;		   break;
			case Keyboard::Key::Hyphen:     platformKey = GLFW_KEY_MINUS;		   break;
			case Keyboard::Key::Period:     platformKey = GLFW_KEY_PERIOD;		   break;
			case Keyboard::Key::Slash:      platformKey = GLFW_KEY_SLASH;		   break;
			case Keyboard::Key::Num0:       platformKey = GLFW_KEY_0;			   break;
			case Keyboard::Key::Num1:       platformKey = GLFW_KEY_1;			   break;
			case Keyboard::Key::Num2:       platformKey = GLFW_KEY_2;			   break;
			case Keyboard::Key::Num3:       platformKey = GLFW_KEY_3;			   break;
			case Keyboard::Key::Num4:       platformKey = GLFW_KEY_4;			   break;
			case Keyboard::Key::Num5:       platformKey = GLFW_KEY_5;			   break;
			case Keyboard::Key::Num6:       platformKey = GLFW_KEY_6;			   break;
			case Keyboard::Key::Num7:       platformKey = GLFW_KEY_7;			   break;
			case Keyboard::Key::Num8:       platformKey = GLFW_KEY_8;			   break;
			case Keyboard::Key::Num9:       platformKey = GLFW_KEY_9;			   break;
			case Keyboard::Key::Semicolon:  platformKey = GLFW_KEY_SEMICOLON;	   break;
			case Keyboard::Key::Equal:      platformKey = GLFW_KEY_EQUAL;		   break;
			case Keyboard::Key::A:          platformKey = GLFW_KEY_A;			   break;
			case Keyboard::Key::B:          platformKey = GLFW_KEY_B;			   break;
			case Keyboard::Key::C:          platformKey = GLFW_KEY_C;			   break;
			case Keyboard::Key::D:          platformKey = GLFW_KEY_D;			   break;
			case Keyboard::Key::E:          platformKey = GLFW_KEY_E;			   break;
			case Keyboard::Key::F:          platformKey = GLFW_KEY_F;			   break;
			case Keyboard::Key::G:          platformKey = GLFW_KEY_G;			   break;
			case Keyboard::Key::H:          platformKey = GLFW_KEY_H;			   break;
			case Keyboard::Key::I:          platformKey = GLFW_KEY_I;			   break;
			case Keyboard::Key::J:          platformKey = GLFW_KEY_J;			   break;
			case Keyboard::Key::K:          platformKey = GLFW_KEY_K;			   break;
			case Keyboard::Key::L:          platformKey = GLFW_KEY_L;			   break;
			case Keyboard::Key::M:          platformKey = GLFW_KEY_M;			   break;
			case Keyboard::Key::N:          platformKey = GLFW_KEY_N;			   break;
			case Keyboard::Key::O:          platformKey = GLFW_KEY_O;			   break;
			case Keyboard::Key::P:          platformKey = GLFW_KEY_P;			   break;
			case Keyboard::Key::Q:          platformKey = GLFW_KEY_Q;			   break;
			case Keyboard::Key::R:          platformKey = GLFW_KEY_R;			   break;
			case Keyboard::Key::S:          platformKey = GLFW_KEY_S;			   break;
			case Keyboard::Key::T:          platformKey = GLFW_KEY_T;			   break;
			case Keyboard::Key::U:          platformKey = GLFW_KEY_U;			   break;
			case Keyboard::Key::V:          platformKey = GLFW_KEY_V;			   break;
			case Keyboard::Key::W:          platformKey = GLFW_KEY_W;			   break;
			case Keyboard::Key::X:          platformKey = GLFW_KEY_X;			   break;
			case Keyboard::Key::Y:          platformKey = GLFW_KEY_Y;			   break;
			case Keyboard::Key::Z:          platformKey = GLFW_KEY_Z;			   break;
			case Keyboard::Key::LBracket:   platformKey = GLFW_KEY_LEFT_BRACKET;   break;
			case Keyboard::Key::Backslash:  platformKey = GLFW_KEY_BACKSLASH;	   break;
			case Keyboard::Key::RBracket:   platformKey = GLFW_KEY_RIGHT_BRACKET;  break;
			case Keyboard::Key::Escape:     platformKey = GLFW_KEY_ESCAPE;		   break;
			case Keyboard::Key::Enter:      platformKey = GLFW_KEY_ENTER;		   break;
			case Keyboard::Key::Tab:        platformKey = GLFW_KEY_TAB;			   break;
			case Keyboard::Key::Backspace:  platformKey = GLFW_KEY_BACKSPACE;	   break;
			case Keyboard::Key::Insert:     platformKey = GLFW_KEY_INSERT;		   break;
			case Keyboard::Key::Delete:     platformKey = GLFW_KEY_DELETE;		   break;
			case Keyboard::Key::Right:      platformKey = GLFW_KEY_RIGHT;		   break;
			case Keyboard::Key::Left:       platformKey = GLFW_KEY_LEFT;		   break;
			case Keyboard::Key::Down:       platformKey = GLFW_KEY_DOWN;		   break;
			case Keyboard::Key::Up:         platformKey = GLFW_KEY_UP;			   break;
			case Keyboard::Key::PageUp:     platformKey = GLFW_KEY_PAGE_UP;		   break;
			case Keyboard::Key::PageDown:   platformKey = GLFW_KEY_PAGE_DOWN;	   break;
			case Keyboard::Key::Home:       platformKey = GLFW_KEY_HOME;		   break;
			case Keyboard::Key::End:        platformKey = GLFW_KEY_END;			   break;
			case Keyboard::Key::Pause:      platformKey = GLFW_KEY_PAUSE;		   break;
			case Keyboard::Key::F1:         platformKey = GLFW_KEY_F1;			   break;
			case Keyboard::Key::F2:         platformKey = GLFW_KEY_F2;			   break;
			case Keyboard::Key::F3:         platformKey = GLFW_KEY_F3;			   break;
			case Keyboard::Key::F4:         platformKey = GLFW_KEY_F4;			   break;
			case Keyboard::Key::F5:         platformKey = GLFW_KEY_F5;			   break;
			case Keyboard::Key::F6:         platformKey = GLFW_KEY_F6;			   break;
			case Keyboard::Key::F7:         platformKey = GLFW_KEY_F7;			   break;
			case Keyboard::Key::F8:         platformKey = GLFW_KEY_F8;			   break;
			case Keyboard::Key::F9:         platformKey = GLFW_KEY_F9;			   break;
			case Keyboard::Key::F10:        platformKey = GLFW_KEY_F10;			   break;
			case Keyboard::Key::F11:        platformKey = GLFW_KEY_F11;			   break;
			case Keyboard::Key::F12:        platformKey = GLFW_KEY_F12;			   break;
			case Keyboard::Key::F13:        platformKey = GLFW_KEY_F13;			   break;
			case Keyboard::Key::F14:        platformKey = GLFW_KEY_F14;			   break;
			case Keyboard::Key::F15:        platformKey = GLFW_KEY_F15;			   break;
			case Keyboard::Key::Numpad0:    platformKey = GLFW_KEY_KP_0;		   break;
			case Keyboard::Key::Numpad1:    platformKey = GLFW_KEY_KP_1;		   break;
			case Keyboard::Key::Numpad2:    platformKey = GLFW_KEY_KP_2;		   break;
			case Keyboard::Key::Numpad3:    platformKey = GLFW_KEY_KP_3;		   break;
			case Keyboard::Key::Numpad4:    platformKey = GLFW_KEY_KP_4;		   break;
			case Keyboard::Key::Numpad5:    platformKey = GLFW_KEY_KP_5;		   break;
			case Keyboard::Key::Numpad6:    platformKey = GLFW_KEY_KP_6;		   break;
			case Keyboard::Key::Numpad7:    platformKey = GLFW_KEY_KP_7;		   break;
			case Keyboard::Key::Numpad8:    platformKey = GLFW_KEY_KP_8;		   break;
			case Keyboard::Key::Numpad9:    platformKey = GLFW_KEY_KP_9;		   break;
			case Keyboard::Key::LShift:     platformKey = GLFW_KEY_LEFT_SHIFT;	   break;
			case Keyboard::Key::LControl:   platformKey = GLFW_KEY_LEFT_CONTROL;   break;
			case Keyboard::Key::LAlt:       platformKey = GLFW_KEY_LEFT_ALT;	   break;
			case Keyboard::Key::LSystem:    platformKey = GLFW_KEY_LEFT_SUPER;	   break;
			case Keyboard::Key::RShift:     platformKey = GLFW_KEY_RIGHT_SHIFT;	   break;
			case Keyboard::Key::RControl:   platformKey = GLFW_KEY_RIGHT_CONTROL;  break;
			case Keyboard::Key::RAlt:       platformKey = GLFW_KEY_RIGHT_ALT;	   break;
			case Keyboard::Key::RSystem:    platformKey = GLFW_KEY_RIGHT_SUPER;	   break;
			case Keyboard::Key::Menu:       platformKey = GLFW_KEY_MENU;		   break;

			default:                        platformKey = GLFW_KEY_UNKNOWN;		   break;
		}

		return platformKey;
	}

}

#endif