module;

#include <memory>

#include <Mikrokosmos/Graphics/Rendering/Direct3D11/Direct3D11.h>

export module Mikrokosmos.Graphics.Rendering.Direct3D11Renderer;

import Mikrokosmos.Graphics.Rendering.Renderer;

export namespace mk
{

	class Direct3D11Renderer : public Renderer
	{

	public:

		Direct3D11Renderer();

		void Initialize() override;
		void Render()     override;
		void Shutdown()   override;

	private:

		ComPtr<IDXGIFactory> _factory;
	};

}

module :private;

namespace mk
{
	
	Direct3D11Renderer::Direct3D11Renderer()
	{
		ThrowIfFailed(
			CreateDXGIFactory(
				IID_PPV_ARGS(_factory.ReleaseAndGetAddressOf())
			)
		);
	}

	void Direct3D11Renderer::Initialize()
	{
		
	}

	void Direct3D11Renderer::Render()
	{

	}

	void Direct3D11Renderer::Shutdown()
	{

	}

}