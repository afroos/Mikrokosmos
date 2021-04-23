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

		struct Properties
		{
			std::string name       = "Mikrokosmos Application";
			Vector2u    windowSize = { 1280, 720 };
			std::string renderer   = "OpenGL";
		};

		Application(const Properties& properties);
		virtual ~Application();

		Application(const Application&)            = delete;
		Application(Application&&)                 = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&)      = delete;

		void Initialize();
		void Run();
		void MainLoop();
		void Shutdown();

		virtual void OnInitialize() {}
		virtual void OnShutdown()   {}
		void OnEvent(Event& event);

		void PushLayer   (Layer* layer);
		void PushOverlay (Layer* layer);

		static Application& Get();

		Window& Window() const;

		mk::DebugLayer* DebugLayer();

	private:

		void OnWindowClosedEvent(WindowClosedEvent& event);
		void OnWindowResizedEvent(WindowResizedEvent& event);

	private:

		inline static Application* _instance { nullptr };

		std::unique_ptr<mk::Window> _window;

		LayerStack _layerStack;

		mk::DebugLayer* _debugLayer;

		bool _running   { true  };
		bool _minimized { false };

		GraphicsSystem _graphicsSystem;

		unsigned int vertexArrayId, vertexBufferId, indexBufferId;

	};

}