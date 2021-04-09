module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.SwapChain;

import Mikrokosmos.UI.Window;

export namespace mk
{

	struct SwapChainDescription
	{
		SwapChainDescription() = default;

		mk::Window* window;
	};

	class SwapChain
	{

	public:

		SwapChain() = delete;
		
		SwapChain(const SwapChainDescription& description);

		virtual ~SwapChain() = default;

		virtual void Present() = 0;

		//mk::Window& Window();

		//Resize();

	protected:

		mk::Window* _window;

	};

}

module :private;

namespace mk
{

	SwapChain::SwapChain(const SwapChainDescription& description)
		: _window { description.window }
	{

	}

	/*mk::Window& SwapChain::Window()
	{
		return *_window;
	}*/
}