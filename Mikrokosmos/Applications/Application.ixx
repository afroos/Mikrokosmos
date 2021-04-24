module;

#include <memory>
#include <string>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Applications.LayerStack;
import Mikrokosmos.Events;
import Mikrokosmos.Graphics;
import Mikrokosmos.Mathematics;
import Mikrokosmos.UI.Window;

export namespace mk
{
	class DebugLayer;

	class Application
	{

	public:

		struct Description
		{
			std::string name       = "Mikrokosmos Application";
			Vector2u    windowSize = { 1280, 720 };
			std::string renderer   = "OpenGL";
		};

		Application(const Description& description);
		virtual ~Application();

		Application(const Application&)            = delete;
		Application(Application&&)                 = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&)      = delete;

		void Run();

		void OnEvent(Event& event);

		static Application& Get();

		Window& Window() const;

		mk::DebugLayer* DebugLayer();

	protected:

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:

		void OnWindowClosedEvent(WindowClosedEvent& event);
		void OnWindowResizedEvent(WindowResizedEvent& event);

	private:

		inline static Application* _instance{ nullptr };

		std::string _name;
		std::unique_ptr<mk::Window> _window;

		GraphicsSystem _graphicsSystem;

		LayerStack _layerStack;

		mk::DebugLayer* _debugLayer;

		bool _running   { true  };
		bool _minimized { false };

		unsigned int vertexArrayId, vertexBufferId, indexBufferId;

	};

}