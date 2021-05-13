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
			std::string renderer   = "Direct3D11";
		};

		Application(const Description& description);
		virtual ~Application();

		Application(const Application&)            = delete;
		Application(Application&&)                 = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&)      = delete;

		static Application& Get();

		virtual void OnInitialize()         {};
		virtual void OnShutdown()           {};
		virtual void OnSuspend()            {};
		virtual void OnResume()             {};
		virtual void OnUpdate()             {};
		virtual void OnEvent(Event& event);

		void Run();
		void MainLoop();

		Window& Window() const;

		mk::DebugLayer* DebugLayer();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:

		void OnWindowClosedEvent(WindowClosedEvent& event);
		void OnWindowResizedEvent(WindowResizedEvent& event);

	private:

		inline static Application*  _instance  { nullptr };

		std::string                 _name;
		std::unique_ptr<mk::Window> _window;
		bool                        _running        { true  };
		bool                        _minimized      { false };
		bool                        _suspended      { false };
		GraphicsSystem              _graphicsSystem;
		LayerStack                  _layerStack;
		mk::DebugLayer*             _debugLayer;

	};

}