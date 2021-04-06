module;

#include <Mikrokosmos/Core.h>
#include <ranges>
#include <glad/glad.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Applications.LayerStack;
import Mikrokosmos.Diagnostics.Logger;
import Mikrokosmos.Events;
import Mikrokosmos.UI.Window;

export namespace mk
{

	class Application
	{

	public:

		MK_API Application();
		MK_API virtual ~Application();

		Application(const Application&)            = delete;
		Application(Application&&)                 = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&)      = delete;

		MK_API Window& Window() const;

		MK_API void Run();

		MK_API void OnEvent(Event& event);

		MK_API void PushLayer   (Layer* layer);
		MK_API void PushOverlay (Layer* layer);

		MK_API static Application& Get();

	private:

		void OnWindowClosedEvent(WindowClosedEvent& event);
		void OnWindowResizedEvent(WindowResizedEvent& event);

	private:

		inline static Application* _instance { nullptr };

		std::unique_ptr<mk::Window> _window;

		LayerStack _layerStack;

		bool _running   { true  };
		bool _minimized { false };

	};

}

module :private;

namespace mk
{

	Application::Application()
	{
		// Singleton assert?
		_instance = this;
		_window = Window::Create();
		_window->callback.Bind(this, &Application::OnEvent);
	}


	Application::~Application()
	{

	}

	Window& Application::Window() const
	{
		return *_window;
	}

	void Application::Run()
	{
		mk::Trace("Application started.");

		while (_running)
		{
			if (!_minimized)
			{
			}

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : _layerStack)
			{
				layer->OnUpdate();
			}

			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher{ event };

		dispatcher.Dispatch<WindowClosedEvent >(this, &Application::OnWindowClosedEvent);
		dispatcher.Dispatch<WindowResizedEvent>(this, &Application::OnWindowResizedEvent);

		mk::Trace("{0}", event);

		for (auto* layer : std::ranges::reverse_view{ _layerStack })
		{
			layer->OnEvent(event);
			if (event.Handled()) break;
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		_layerStack.PushOverlay(layer);
		layer->OnAttach();

	}

	Application& Application::Get()
	{
		return *_instance;
	}

	void Application::OnWindowClosedEvent(WindowClosedEvent& event)
	{
		_running = false;
		event.Handled(true);
	}

	void Application::OnWindowResizedEvent(WindowResizedEvent& event)
	{
		//_minimized = (event.NewSize() == Vector2u::Zero());
		_minimized = true;
		event.Handled(true);
	}

}