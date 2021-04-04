module;

#include <Mikrokosmos/Core.h>
#include <Mikrokosmos/Platform/OpenGL/ImGuiOpenGLRenderer.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

export module Mikrokosmos.Applications.DebugLayer;

import Mikrokosmos.Applications.Application;
import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Events;

namespace mk
{
	export
	{

		class MK_API DebugLayer : public Layer
		{

		public:

			 DebugLayer(Application& application);
			~DebugLayer();

			void OnAttach();
			void OnDetach();

			void OnUpdate();
			void OnEvent(Event& event);

		private:

			void OnMouseButtonPressedEvent  (MouseButtonPressedEvent&  event);
			void OnMouseButtonReleasedEvent (MouseButtonReleasedEvent& event);
			void OnMouseMovedEvent          (MouseMovedEvent&          event);
			void OnMouseScrolledEvent       (MouseScrolledEvent&       event);
			void OnKeyPressedEvent          (KeyPressedEvent&          event);
			void OnKeyReleasedEvent         (KeyReleasedEvent&         event);
			void OnCharacterTypedEvent      (CharacterTypedEvent&      event);
			void OnWindowResizedEvent       (WindowResizedEvent&       event);

		private:

		};

	}
	
}

module : private;

namespace mk
{

	constexpr int MapButton(Mouse::Button button)
	{
		switch (button)
		{
			case Mouse::Button::Left:      return 0;
			case Mouse::Button::Right:     return 1;
			case Mouse::Button::Middle:    return 2;

			default:                       return -1;
		}
	}

	constexpr int MapKey(Keyboard::Key key)
	{
		switch(key)
		{
			case Keyboard::Key::Space:     return GLFW_KEY_SPACE;
			case Keyboard::Key::Quote:     return GLFW_KEY_APOSTROPHE;
			case Keyboard::Key::Comma:     return GLFW_KEY_COMMA;
			case Keyboard::Key::Hyphen:    return GLFW_KEY_MINUS;
			case Keyboard::Key::Period:    return GLFW_KEY_PERIOD;
			case Keyboard::Key::Slash:     return GLFW_KEY_SLASH;
			case Keyboard::Key::Num0:      return GLFW_KEY_0;
			case Keyboard::Key::Num1:      return GLFW_KEY_1;
			case Keyboard::Key::Num2:      return GLFW_KEY_2;
			case Keyboard::Key::Num3:      return GLFW_KEY_3;
			case Keyboard::Key::Num4:      return GLFW_KEY_4;
			case Keyboard::Key::Num5:      return GLFW_KEY_5;
			case Keyboard::Key::Num6:      return GLFW_KEY_6;
			case Keyboard::Key::Num7:      return GLFW_KEY_7;
			case Keyboard::Key::Num8:      return GLFW_KEY_8;
			case Keyboard::Key::Num9:      return GLFW_KEY_9;
			case Keyboard::Key::Semicolon: return GLFW_KEY_SEMICOLON;
			case Keyboard::Key::Equal:     return GLFW_KEY_EQUAL;
			case Keyboard::Key::A:         return GLFW_KEY_A;
			case Keyboard::Key::B:         return GLFW_KEY_B;
			case Keyboard::Key::C:         return GLFW_KEY_C;
			case Keyboard::Key::D:         return GLFW_KEY_D;
			case Keyboard::Key::E:         return GLFW_KEY_E;
			case Keyboard::Key::F:         return GLFW_KEY_F;
			case Keyboard::Key::G:         return GLFW_KEY_G;
			case Keyboard::Key::H:         return GLFW_KEY_H;
			case Keyboard::Key::I:         return GLFW_KEY_I;
			case Keyboard::Key::J:         return GLFW_KEY_J;
			case Keyboard::Key::K:         return GLFW_KEY_K;
			case Keyboard::Key::L:         return GLFW_KEY_L;
			case Keyboard::Key::M:         return GLFW_KEY_M;
			case Keyboard::Key::N:         return GLFW_KEY_N;
			case Keyboard::Key::O:         return GLFW_KEY_O;
			case Keyboard::Key::P:         return GLFW_KEY_P;
			case Keyboard::Key::Q:         return GLFW_KEY_Q;
			case Keyboard::Key::R:         return GLFW_KEY_R;
			case Keyboard::Key::S:         return GLFW_KEY_S;
			case Keyboard::Key::T:         return GLFW_KEY_T;
			case Keyboard::Key::U:         return GLFW_KEY_U;
			case Keyboard::Key::V:         return GLFW_KEY_V;
			case Keyboard::Key::W:         return GLFW_KEY_W;
			case Keyboard::Key::X:         return GLFW_KEY_X;
			case Keyboard::Key::Y:         return GLFW_KEY_Y;
			case Keyboard::Key::Z:         return GLFW_KEY_Z;
			case Keyboard::Key::LBracket:  return GLFW_KEY_LEFT_BRACKET;
			case Keyboard::Key::Backslash: return GLFW_KEY_BACKSLASH;
			case Keyboard::Key::RBracket:  return GLFW_KEY_RIGHT_BRACKET;
			case Keyboard::Key::Escape:    return GLFW_KEY_ESCAPE;
			case Keyboard::Key::Enter:     return GLFW_KEY_ENTER;
			case Keyboard::Key::Tab:       return GLFW_KEY_TAB;
			case Keyboard::Key::Backspace: return GLFW_KEY_BACKSPACE;
			case Keyboard::Key::Insert:    return GLFW_KEY_INSERT;
			case Keyboard::Key::Delete:    return GLFW_KEY_DELETE;
			case Keyboard::Key::Right:     return GLFW_KEY_RIGHT;
			case Keyboard::Key::Left:      return GLFW_KEY_LEFT;
			case Keyboard::Key::Down:      return GLFW_KEY_DOWN;
			case Keyboard::Key::Up:        return GLFW_KEY_UP;
			case Keyboard::Key::PageUp:    return GLFW_KEY_PAGE_UP;
			case Keyboard::Key::PageDown:  return GLFW_KEY_PAGE_DOWN;
			case Keyboard::Key::Home:      return GLFW_KEY_HOME;
			case Keyboard::Key::End:       return GLFW_KEY_END;
			case Keyboard::Key::Pause:     return GLFW_KEY_PAUSE;
			case Keyboard::Key::F1:        return GLFW_KEY_F1; 
			case Keyboard::Key::F2:        return GLFW_KEY_F2; 
			case Keyboard::Key::F3:        return GLFW_KEY_F3; 
			case Keyboard::Key::F4:        return GLFW_KEY_F4; 
			case Keyboard::Key::F5:        return GLFW_KEY_F5; 
			case Keyboard::Key::F6:        return GLFW_KEY_F6; 
			case Keyboard::Key::F7:        return GLFW_KEY_F7; 
			case Keyboard::Key::F8:        return GLFW_KEY_F8; 
			case Keyboard::Key::F9:        return GLFW_KEY_F9; 
			case Keyboard::Key::F10:       return GLFW_KEY_F10;
			case Keyboard::Key::F11:       return GLFW_KEY_F11;
			case Keyboard::Key::F12:       return GLFW_KEY_F12;
			case Keyboard::Key::F13:       return GLFW_KEY_F13;
			case Keyboard::Key::F14:       return GLFW_KEY_F14;
			case Keyboard::Key::F15:       return GLFW_KEY_F15;
			case Keyboard::Key::Numpad0:   return GLFW_KEY_KP_0;
			case Keyboard::Key::Numpad1:   return GLFW_KEY_KP_1;
			case Keyboard::Key::Numpad2:   return GLFW_KEY_KP_2;
			case Keyboard::Key::Numpad3:   return GLFW_KEY_KP_3;
			case Keyboard::Key::Numpad4:   return GLFW_KEY_KP_4;
			case Keyboard::Key::Numpad5:   return GLFW_KEY_KP_5;
			case Keyboard::Key::Numpad6:   return GLFW_KEY_KP_6;
			case Keyboard::Key::Numpad7:   return GLFW_KEY_KP_7;
			case Keyboard::Key::Numpad8:   return GLFW_KEY_KP_8;
			case Keyboard::Key::Numpad9:   return GLFW_KEY_KP_9;
			case Keyboard::Key::LShift:    return GLFW_KEY_LEFT_SHIFT;
			case Keyboard::Key::LControl:  return GLFW_KEY_LEFT_CONTROL;
			case Keyboard::Key::LAlt:      return GLFW_KEY_LEFT_ALT;
			case Keyboard::Key::LSystem:   return GLFW_KEY_LEFT_SUPER;
			case Keyboard::Key::RShift:    return GLFW_KEY_RIGHT_SHIFT;
			case Keyboard::Key::RControl:  return GLFW_KEY_RIGHT_CONTROL;
			case Keyboard::Key::RAlt:      return GLFW_KEY_RIGHT_ALT;
			case Keyboard::Key::RSystem:   return GLFW_KEY_RIGHT_SUPER;
			case Keyboard::Key::Menu:      return GLFW_KEY_MENU;
			
			default:                       return GLFW_KEY_UNKNOWN;
		}
	}

	DebugLayer::DebugLayer(Application& application)
		:
		Layer{ application }
	{

	}

	DebugLayer::~DebugLayer()
	{

	}

	void DebugLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		auto& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void DebugLayer::OnDetach()
	{

	}

	void DebugLayer::OnUpdate()
	{
		auto& io = ImGui::GetIO();
		io.DisplaySize = ImVec2{ static_cast<float>(_application.Window().Width()), 
			                                                                                                                                                                                                                   static_cast<float>(_application.Window().Height()) };

		auto time = (float)glfwGetTime();
		io.DeltaTime = 1.0f / 60.0f;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void DebugLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher{ event };

		dispatcher.Dispatch<MouseButtonPressedEvent >(this, &DebugLayer::OnMouseButtonPressedEvent );
		dispatcher.Dispatch<MouseButtonReleasedEvent>(this, &DebugLayer::OnMouseButtonReleasedEvent);
		dispatcher.Dispatch<MouseMovedEvent         >(this, &DebugLayer::OnMouseMovedEvent         );
		dispatcher.Dispatch<MouseScrolledEvent      >(this, &DebugLayer::OnMouseScrolledEvent      );
		dispatcher.Dispatch<KeyPressedEvent         >(this, &DebugLayer::OnKeyPressedEvent         );
		dispatcher.Dispatch<KeyReleasedEvent        >(this, &DebugLayer::OnKeyReleasedEvent        );
		dispatcher.Dispatch<CharacterTypedEvent     >(this, &DebugLayer::OnCharacterTypedEvent     );
		dispatcher.Dispatch<WindowResizedEvent      >(this, &DebugLayer::OnWindowResizedEvent      );
	}

	void DebugLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		auto& io = ImGui::GetIO();
		io.MouseDown[MapButton(event.Button())] = true;
	}

	void DebugLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		auto& io = ImGui::GetIO();
		io.MouseDown[MapButton(event.Button())] = false;
	}

	void DebugLayer::OnMouseMovedEvent(MouseMovedEvent& event)
	{
		auto& io = ImGui::GetIO();
		io.MousePos = ImVec2{ static_cast<float>(event.NewPosition().X()), 
							                     static_cast<float>(event.NewPosition().Y())};
	}

	void DebugLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		auto& io = ImGui::GetIO();
		io.MouseWheelH += static_cast<float>(event.Offset().X());
		io.MouseWheel                     += static_cast<float>(event.Offset().Y());
	}

	void DebugLayer::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		auto& io = ImGui::GetIO();
		io.KeysDown[MapKey(event.Key())] = true;

		io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
	}

	void DebugLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
	{
		auto& io = ImGui::GetIO();
		io.KeysDown[MapKey(event.Key())] = false;
	}

	void DebugLayer::OnCharacterTypedEvent(CharacterTypedEvent& event)
	{
		auto& io = ImGui::GetIO();
		auto character = event.Character();

		if (character > 0 && character < 0x10000)
			io.AddInputCharacter(static_cast<unsigned short>(character));
	}

	void DebugLayer::OnWindowResizedEvent(WindowResizedEvent& event)
	{
		auto& io = ImGui::GetIO();
		io.DisplaySize = ImVec2{ static_cast<float>(event.NewSize().X()),
							                                           static_cast<float>(event.NewSize().Y()) };
		io.DisplayFramebufferScale = ImVec2{ 1.0f, 1.0f };
		glViewport(0, 0, event.NewSize().X(), event.NewSize().Y());
	}
}