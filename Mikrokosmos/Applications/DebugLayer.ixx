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
			/*void OnKeyPressedEvent          (KeyPressedEvent&          event);
			void OnKeyReleasedEvent         (KeyReleasedEvent&         event);
			void OnKeyTypedEvent            (KeyTypedEvent&            event);*/
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
			case Mouse::Button::Left:   return  0;
			case Mouse::Button::Right:  return  1;
			case Mouse::Button::Middle: return  2;

			default:                    return -1;
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
		io.MouseWheel  += static_cast<float>(event.Offset().Y());
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