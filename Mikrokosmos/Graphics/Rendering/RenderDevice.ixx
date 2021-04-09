module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.RenderDevice;

//import Mikrokosmos.Events.Event;

export namespace mk
{

	struct RenderDeviceDescription
	{
		RenderDeviceDescription() = default;
	};

	class RenderDevice
	{

	public:

		RenderDevice() = delete;
		RenderDevice(const RenderDeviceDescription& description = {});

		virtual ~RenderDevice() = default;

		virtual void Method() {}

	};

}

module :private;

namespace mk
{
	RenderDevice::RenderDevice(const RenderDeviceDescription& description)
	{

	}
}