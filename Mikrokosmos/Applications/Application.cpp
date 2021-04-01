module;

#include <ranges>
#include <Mikrokosmos/Core.h>
#include <glad/glad.h>

module Mikrokosmos.Applications.Application;

//import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Diagnostics.Logger;

namespace mk
{
	Application::Application()
	{
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
				layer->OnUpdate();
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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		_layerStack.PushOverlay(layer);
		layer->OnAttach();

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