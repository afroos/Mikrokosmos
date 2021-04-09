module;

#include <Mikrokosmos/Core.h>
#include <ranges>
#include <glad/glad.h>

module Mikrokosmos.Applications.Application;

import Mikrokosmos.Applications.DebugLayer;
import Mikrokosmos.Diagnostics.Logger;
import Mikrokosmos.Graphics;

namespace mk
{

	Application::Application()
	{
		// Singleton assert?
		_instance = this;
		_window = Window::Create();
		_window->callback.Bind(this, &Application::OnEvent);

		_debugLayer = new mk::DebugLayer();
		PushOverlay(_debugLayer);

		InitializeGraphics();
	}


	Application::~Application()
	{

	}

	Window& Application::Window() const
	{
		return *_window;
	}

	void Application::InitializeGraphics()
	{
		_renderer      = GraphicsSystem::CreateRenderer("OpenGL");
		
		_renderDevice  = _renderer->CreateRenderDevice(mk::RenderDeviceDescription{});
		
		_deviceContext = _renderer->CreateDeviceContext(mk::DeviceContextDescription{});
		
		mk::SwapChainDescription swapChainDescription;
		swapChainDescription.window = _window.get();
		
		_swapChain = _renderer->CreateSwapChain(swapChainDescription);
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

			_debugLayer->Begin();
			{
				for (auto layer : _layerStack)
				{
					layer->OnRender();
				}
			}
			_debugLayer->End();

			_window->OnUpdate();
			_swapChain->Present();
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

	mk::DebugLayer* Application::DebugLayer()
	{
		return _debugLayer;
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