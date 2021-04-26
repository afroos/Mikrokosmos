module;

#include <memory>
#include <string>

export module Mikrokosmos.Graphics.Rendering.Renderer;

import Mikrokosmos.Graphics.Rendering.DeviceContext;
import Mikrokosmos.Graphics.Rendering.RenderDevice;
import Mikrokosmos.Graphics.Rendering.SwapChain;

export namespace mk
{

	class Renderer
	{

	public:

		struct Description
		{
			Description() = default;
			~Description() = default;

			std::string name = "";

		};

		Renderer() = default;
		
		virtual ~Renderer() = default;

		//virtual std::unique_ptr<RenderDevice>  CreateRenderDevice  (const RenderDevice::Description&  description ) = 0;
		//virtual std::unique_ptr<DeviceContext> CreateDeviceContext (const DeviceContext::Description& description ) = 0;
		//virtual std::unique_ptr<SwapChain>     CreateSwapChain     (const SwapChain::Description&     description ) = 0;

		virtual void Initialize() {};
		virtual void Render()     {};
		virtual void Shutdown()   {};

	};


}

module :private;

namespace mk
{

}