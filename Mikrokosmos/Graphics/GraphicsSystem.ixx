module;

#include <memory>
#include <string>

export module Mikrokosmos.Graphics.GraphicsSystem;

import Mikrokosmos.Graphics.Rendering;
import Mikrokosmos.UI.Window;

export namespace mk
{

	class GraphicsSystem
	{

	public:

		struct Description
		{
			std::string renderer = "OpenGL";
			Window*     window   = nullptr;
		};

		GraphicsSystem(const Description& description);

		void Render();

	private:

		std::unique_ptr<Renderer> CreateRenderer(const std::string& name);

	private:

		std::unique_ptr<Renderer>      _renderer;
		std::unique_ptr<RenderDevice>  _renderDevice;
		std::unique_ptr<DeviceContext> _deviceContext;
		std::unique_ptr<SwapChain>     _swapChain;

	};

}