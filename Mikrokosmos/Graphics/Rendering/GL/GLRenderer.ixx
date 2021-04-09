module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.GLRenderer;

import Mikrokosmos.Graphics.Rendering.GLDeviceContext;
import Mikrokosmos.Graphics.Rendering.GLRenderDevice;
import Mikrokosmos.Graphics.Rendering.GLSwapChain;
import Mikrokosmos.Graphics.Rendering.Renderer;

export namespace mk
{

	class GLRenderer : public Renderer
	{

	public:

		GLRenderer() = default;

		std::unique_ptr<RenderDevice>  CreateRenderDevice  (const RenderDeviceDescription& description ) override;
		std::unique_ptr<DeviceContext> CreateDeviceContext (const DeviceContextDescription& description) override;
		std::unique_ptr<SwapChain>     CreateSwapChain     (const SwapChainDescription& description    ) override;

	private:

	};


}

module :private;

namespace mk
{

	std::unique_ptr<RenderDevice> GLRenderer::CreateRenderDevice(const RenderDeviceDescription& description)
	{
		return std::make_unique<GLRenderDevice>(description);
	}

	std::unique_ptr<DeviceContext> GLRenderer::CreateDeviceContext(const DeviceContextDescription& description)
	{
		return std::make_unique<GLDeviceContext>(description);
	}

	std::unique_ptr<SwapChain> GLRenderer::CreateSwapChain(const SwapChainDescription& description)
	{
		return std::make_unique<GLSwapChain>(description);
	}

}