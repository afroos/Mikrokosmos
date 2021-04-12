module;

#include <Mikrokosmos/Core.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module Mikrokosmos.Graphics.Rendering.GLSwapChain;

import Mikrokosmos.Diagnostics.Logger;
import Mikrokosmos.Graphics.Rendering.SwapChain;

export namespace mk
{

	class GLSwapChain : public SwapChain
	{

	public:

		GLSwapChain() = delete;
		GLSwapChain(const SwapChain::Description& description);

		void Present() override;

	private:

		GLFWwindow* _nativeWindow;

	};

}

module :private;

namespace mk
{
	GLSwapChain::GLSwapChain(const SwapChain::Description& description)
		: SwapChain{ description }
	{
		_nativeWindow = reinterpret_cast<GLFWwindow*>(_window->NativeHandle());
		
		// Todo: move initialization code below to proper location on the Renderer class.
		glfwMakeContextCurrent(_nativeWindow);
		auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		mk::Info("Renderer Info:");
		mk::Info("  Vendor: {0}",   glGetString(GL_VENDOR)  );
		mk::Info("  Renderer: {0}", glGetString(GL_RENDERER));
		mk::Info("  Version: {0}",  glGetString(GL_VERSION) );
	}

	void GLSwapChain::Present()
	{
		glfwSwapBuffers(_nativeWindow);
	}

}