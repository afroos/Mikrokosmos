module;

export module Mikrokosmos.Graphics.Rendering.GLRenderDevice;

import Mikrokosmos.Graphics.Rendering.Device;


export namespace mk
{

	class GLRenderDevice : public Device
	{

	public:

		GLRenderDevice() = delete;
		GLRenderDevice(const Device::Description& description);

		virtual ~GLRenderDevice() = default;

	};

}

module :private;

namespace mk
{
	GLRenderDevice::GLRenderDevice(const Device::Description& description)
		:
		Device{ description }
	{

	}
}