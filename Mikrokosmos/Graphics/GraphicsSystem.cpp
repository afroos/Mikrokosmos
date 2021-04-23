module;

#include <functional>
#include <map>
#include <memory>

module Mikrokosmos.Graphics.GraphicsSystem;

import Mikrokosmos.Applications.Application;
import Mikrokosmos.Graphics.Rendering.GLRenderer;

namespace mk
{
	GraphicsSystem::GraphicsSystem(const Description& description)
	{
		_renderer = CreateRenderer(description.renderer);
	}
	
	void GraphicsSystem::Initialize()
	{
		_renderDevice = _renderer->CreateRenderDevice(RenderDevice::Description{});

		_deviceContext = _renderer->CreateDeviceContext(DeviceContext::Description{});

		SwapChain::Description swapChainDescription;
		swapChainDescription.window = &Application::Get().Window();

		_swapChain = _renderer->CreateSwapChain(swapChainDescription);
	}

	void GraphicsSystem::Render()
	{
		_swapChain->Present();
	}	
	
	void GraphicsSystem::Shutdown()
	{

	}

	std::unique_ptr<Renderer> GraphicsSystem::CreateRenderer(const std::string& name)
	{
		static std::map<
			std::string, 
			std::function<std::unique_ptr<Renderer>()>> dispatchTable
		{
			{ "OpenGL", []() { return std::make_unique<GLRenderer>(); } }
		};

		auto entry = dispatchTable.find(name);
		if (entry != dispatchTable.end())
		{
			auto [name, instance] = *entry;
			return instance();
		}
		else return nullptr;

	}
}