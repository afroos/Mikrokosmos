module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.GLDeviceContext;

import Mikrokosmos.Graphics.Rendering.DeviceContext;

export namespace mk
{

	class GLDeviceContext : public DeviceContext
	{

	public:

		GLDeviceContext() = delete;

		GLDeviceContext(const DeviceContext::Description& description);

		virtual ~GLDeviceContext() = default;

	};

}

module :private;

namespace mk
{
	GLDeviceContext::GLDeviceContext(const DeviceContext::Description& description)
		: DeviceContext{ description }
	{

	}
}