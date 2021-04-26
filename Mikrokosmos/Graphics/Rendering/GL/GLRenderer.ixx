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

		//std::unique_ptr<RenderDevice>  CreateRenderDevice  (const RenderDevice::Description& description ) override;
		//std::unique_ptr<DeviceContext> CreateDeviceContext (const DeviceContext::Description& description) override;
		//std::unique_ptr<SwapChain>     CreateSwapChain     (const SwapChain::Description& description    ) override;

		void Initialize() override {}
		void Render()     override {}
		void Shutdown()   override {}

	private:

	};


}

module :private;

namespace mk
{

	/*std::unique_ptr<RenderDevice> GLRenderer::CreateRenderDevice(const RenderDevice::Description& description)
	{
		return std::make_unique<GLRenderDevice>(description);
	}

	std::unique_ptr<DeviceContext> GLRenderer::CreateDeviceContext(const DeviceContext::Description& description)
	{
		return std::make_unique<GLDeviceContext>(description);
	}

	std::unique_ptr<SwapChain> GLRenderer::CreateSwapChain(const SwapChain::Description& description)
	{
		return std::make_unique<GLSwapChain>(description);
	}*/

}