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

	Application::Application(const Description& description)
		: _name           { description.name },
		  _window         { Window::Create({.title = _name, .size = description.windowSize }) },
		  _graphicsSystem { {.renderer = description.renderer, .window = _window.get() } },
		  _debugLayer     { new mk::DebugLayer() }
	{
		_instance = this;
	
		_window->EventCallback.Bind(this, &Application::OnEvent);

		_graphicsSystem.Initialize();

		//PushOverlay(_debugLayer);

		// Test:
		/*glGenVertexArrays(1, &vertexArrayId);
		glBindVertexArray(vertexArrayId);

		glGenBuffers(1, &vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	}

	Application::~Application()
	{
		_graphicsSystem.Shutdown();
	}

	void Application::Run()
	{
		mk::Trace("Application started.");

		while (_running)
		{
			_window->ProcessEvents();

			if (!_minimized)
			{
			}

			//glClearColor(0.1f, 0.1f, 0.1f, 1);
			//glClear(GL_COLOR_BUFFER_BIT);

			// Test:
			//glBindVertexArray(vertexArrayId);
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (auto layer : _layerStack)
			{
				layer->OnUpdate();
			}

			//_debugLayer->Begin();
			{
				for (auto layer : _layerStack)
				{
					layer->OnRender();
				}
			}
			//_debugLayer->End();

			_graphicsSystem.Render();
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

	mk::Window& Application::Window() const
	{
		return *_window;
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