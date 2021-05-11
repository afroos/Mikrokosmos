module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.Device;

//import Mikrokosmos.Events.Event;

export namespace mk
{

	class Device
	{

	public:

		struct Description
		{
			Description() = default;
		};

		Device() = delete;
		Device(const Description& description = {});

		virtual ~Device() = default;

		//virtual Buffer* CreateBuffer(const BufferDescription& description = {});
		//Texture* CreateTexture(TextureDescription);
		//Shader* CreateShader(ShaderDescription);
		//Pipeline* CreatePipeline(PipelineDescription);

	};

}

module :private;

namespace mk
{
	Device::Device(const Device::Description& description)
	{

	}
}