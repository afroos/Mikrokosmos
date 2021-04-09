module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.DeviceContext;

//import Mikrokosmos.Events.Event;

export namespace mk
{

	struct DeviceContextDescription
	{
		DeviceContextDescription() = default;
	};

	class DeviceContext
	{

	public:

		DeviceContext() = delete;

		DeviceContext(const DeviceContextDescription& description = {});

		virtual ~DeviceContext() = default;

		virtual void Method() {}

	};

}

module :private;

namespace mk
{
	DeviceContext::DeviceContext(const DeviceContextDescription& description)
	{

	}
}