module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.SwapChain;

import Mikrokosmos.UI.Window;

export namespace mk
{

	class SwapChain
	{

	public:

		struct Description
		{
			mk::Window* window;
		};

		SwapChain() = delete;
		
		SwapChain(const Description& description);

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

	SwapChain::SwapChain(const SwapChain::Description& description)
		: _window { description.window }
	{

	}

	/*mk::Window& SwapChain::Window()
	{
		return *_window;
	}*/

}