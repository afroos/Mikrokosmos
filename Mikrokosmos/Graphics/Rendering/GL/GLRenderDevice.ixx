module;

export module Mikrokosmos.Graphics.Rendering.GLRenderDevice;

import Mikrokosmos.Graphics.Rendering.RenderDevice;


export namespace mk
{

	class GLRenderDevice : public RenderDevice
	{

	public:

		GLRenderDevice() = delete;
		GLRenderDevice(const RenderDevice::Description& description);

		virtual ~GLRenderDevice() = default;

	};

}

module :private;

namespace mk
{
	GLRenderDevice::GLRenderDevice(const RenderDevice::Description& description)
		:
		RenderDevice{ description }
	{

	}
}