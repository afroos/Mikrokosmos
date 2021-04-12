module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.DeviceContext;

//import Mikrokosmos.Events.Event;

export namespace mk
{

	class DeviceContext
	{

	public:

		struct Description
		{
			Description() = default;
		};

		DeviceContext() = delete;

		DeviceContext(const Description& description = {});

		virtual ~DeviceContext() = default;

		virtual void Method() {}

	};

}

module :private;

namespace mk
{
	DeviceContext::DeviceContext(const DeviceContext::Description& description)
	{

	}
}