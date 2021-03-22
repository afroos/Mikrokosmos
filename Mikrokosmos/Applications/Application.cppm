module;

#include <memory>
#include <ranges>

#include <glad/glad.h>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Applications.LayerStack;
import Mikrokosmos.Diagnostics.Logger;
import Mikrokosmos.Events;
import Mikrokosmos.UI.Window;

namespace mk
{
	export
	{

		class MK_API Application
		{

		public:

			Application();
			virtual ~Application() = default;

			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;

			void Run();

			void OnEvent(Event& event);

			void PushLayer   (Layer* layer);
			void PushOverlay (Layer* layer);

		private:

			std::unique_ptr<Window> _window;

			void OnWindowClosed  (WindowClosedEvent&  event);
			void OnWindowResized (WindowResizedEvent& event);

			LayerStack _layerStack;

			bool _running   { true  };
			bool _minimized { false };

		};

	}
	
}

module : private;

namespace mk
{
	Application::Application()
	{
		_window = Window::Create();
		_window->callback.Bind(this, &Application::OnEvent);
	}

	void Application::Run()
	{
		mk::trace("Application started.");

		while (_running)
		{
			if (!_minimized)
			{
			}

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : _layerStack)
			{
				layer->OnUpdate(0.001f);
			}

			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher{ event };

		dispatcher.Dispatch<WindowClosedEvent >(this, &Application::OnWindowClosed);
		dispatcher.Dispatch<WindowResizedEvent>(this, &Application::OnWindowResized);

		mk::trace("{0}", event);
		
		for (auto* layer : std::ranges::reverse_view{ _layerStack })
		{
			//if (event.Handled()) break;

			layer->OnEvent(event);
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		_layerStack.PushOverlay(layer);
	}

	void Application::OnWindowClosed(WindowClosedEvent& event)
	{
		_running = false;
		event.Handled(true);
	}

	void Application::OnWindowResized(WindowResizedEvent& event)
	{
		_minimized = (event.NewSize() == mk::Extent2D{0, 0});
		event.Handled(true);
	}

}