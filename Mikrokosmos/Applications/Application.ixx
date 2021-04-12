module;

#include <memory>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Applications.LayerStack;
import Mikrokosmos.Events;
import Mikrokosmos.Graphics;
import Mikrokosmos.UI.Window;

export namespace mk
{
	class DebugLayer;

	class Application
	{

	public:

		Application();
		virtual ~Application();

		Application(const Application&)            = delete;
		Application(Application&&)                 = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&)      = delete;

		Window& Window() const;

		void Run();

		void OnEvent(Event& event);

		void PushLayer   (Layer* layer);
		void PushOverlay (Layer* layer);

		static Application& Get();

		mk::DebugLayer* DebugLayer();

	private:

		void InitializeGraphics();

		void OnWindowClosedEvent(WindowClosedEvent& event);
		void OnWindowResizedEvent(WindowResizedEvent& event);

	private:

		inline static Application* _instance { nullptr };

		std::unique_ptr<mk::Window> _window;

		LayerStack _layerStack;

		mk::DebugLayer* _debugLayer;

		bool _running   { true  };
		bool _minimized { false };

		std::unique_ptr<Renderer>      _renderer;
		std::unique_ptr<RenderDevice>  _renderDevice;
		std::unique_ptr<DeviceContext> _deviceContext;
		std::unique_ptr<SwapChain>     _swapChain;

		unsigned int vertexArrayId, vertexBufferId, indexBufferId;

	};

}