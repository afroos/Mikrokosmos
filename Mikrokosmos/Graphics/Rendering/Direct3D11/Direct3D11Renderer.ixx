module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.Direct3D11Renderer;

import Mikrokosmos.Graphics.Rendering.Renderer;

export namespace mk
{

	class Direct3D11Renderer : public Renderer
	{

	public:

		Direct3D11Renderer() = default;

		void Initialize() override;
		void Render()     override;
		void Shutdown()   override;

	private:


	};

}

module :private;

namespace mk
{
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