module;

#include <memory>
#include <string>

export module Mikrokosmos.Graphics.Rendering.Renderer;

import Mikrokosmos.Graphics.Rendering.DeviceContext;
import Mikrokosmos.Graphics.Rendering.RenderDevice;
import Mikrokosmos.Graphics.Rendering.SwapChain;

export namespace mk
{

	struct RendererDescription
	{
		RendererDescription()  = default;
		~RendererDescription() = default;

		std::string name = "";

	};

	class Renderer
	{

	public:

		Renderer() = default;
		
		virtual ~Renderer() = default;

		virtual std::unique_ptr<RenderDevice>  CreateRenderDevice  (const RenderDeviceDescription&  description ) = 0;
		virtual std::unique_ptr<DeviceContext> CreateDeviceContext (const DeviceContextDescription& description ) = 0;
		virtual std::unique_ptr<SwapChain>     CreateSwapChain     (const SwapChainDescription&     description ) = 0;

	};


}

module :private;

namespace mk
{

}