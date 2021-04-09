module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module Mikrokosmos.Graphics.Rendering.GLSwapChain;

import Mikrokosmos.Graphics.Rendering.SwapChain;

export namespace mk
{

	class GLSwapChain : public SwapChain
	{

	public:

		GLSwapChain() = delete;
		GLSwapChain(const SwapChainDescription& description);

		void Present() override;

	private:

		GLFWwindow* _nativeWindow;

	};

}

module :private;

namespace mk
{
	GLSwapChain::GLSwapChain(const SwapChainDescription& description)
		: SwapChain{ description }
	{
		_nativeWindow = reinterpret_cast<GLFWwindow*>(_window->NativeHandle());
	}

	void GLSwapChain::Present()
	{
		glfwSwapBuffers(_nativeWindow);
	}

}