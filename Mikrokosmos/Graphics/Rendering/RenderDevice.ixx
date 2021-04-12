module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.RenderDevice;

//import Mikrokosmos.Events.Event;

export namespace mk
{

	class RenderDevice
	{

	public:

		struct Description
		{
			Description() = default;
		};

		RenderDevice() = delete;
		RenderDevice(const Description& description = {});

		virtual ~RenderDevice() = default;

		//virtual Buffer* CreateBuffer(const BufferDescription& description = {});
		//Texture* CreateTexture(TextureDescription);
		//Shader* CreateShader(ShaderDescription);
		//Pipeline* CreatePipeline(PipelineDescription);

	};

}

module :private;

namespace mk
{
	RenderDevice::RenderDevice(const RenderDevice::Description& description)
	{

	}
}