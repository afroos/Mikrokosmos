module;

#include <functional>
#include <map>
#include <memory>

#include <dxgi.h>
#include <d3d11.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h> // TODO: remove.

module Mikrokosmos.Graphics.GraphicsSystem;

import Mikrokosmos.Graphics.Rendering.Direct3D11Renderer;

namespace mk
{
	GraphicsSystem::GraphicsSystem(const Description& description) : 
		_window       { description.window },
		_outputWidth  { _window->Width()   },
		_outputHeight { _window->Height()  }
	{
		_renderer = CreateRenderer(description.renderer);

		//_renderDevice = _renderer->CreateRenderDevice(RenderDevice::Description{});

		//_deviceContext = _renderer->CreateDeviceContext(DeviceContext::Description{});

		//_swapChain = _renderer->CreateSwapChain({ .window = description.window });

		/*void initVulkan() {
					createInstance();
			setupDebugCallback();
					createSurface();
					pickPhysicalDevice();
					createLogicalDevice();
					createSwapChain();
			createImageViews();
			createRenderPass();
			createGraphicsPipeline();
			createFramebuffers();
			createCommandPool();
			createVertexBuffer();
			createCommandBuffers();
			createSyncObjects();
		}*/
	}

	void GraphicsSystem::Initialize()
	{
		//_renderer->Initialize();

		CreateEntryPoint();
		PickAdapter();
		CreateDevice();
		CreateSwapChain();
		CreateRenderTarget();
		CreateDepthStencil();
	}

	void GraphicsSystem::Render()
	{
		//_renderer->Render();

		Clear();
		Present();
	}

	void GraphicsSystem::Shutdown()
	{
		//_renderer->Shutdown();

		// Close and release all existing COM objects
		/*_swapChain->Release();
		_renderTargetView->Release();
		_device->Release();
		_context->Release();*/
	}

	std::unique_ptr<Renderer> GraphicsSystem::CreateRenderer(const std::string& name)
	{
		static std::map<
			std::string, 
			std::function<std::unique_ptr<Renderer>()>> dispatchTable
		{
			{ "Direct3D11", []() { return std::make_unique<Direct3D11Renderer>(); } }/*,
			{ "OpenGL",     []() { return std::make_unique<GLRenderer        >(); } }*/
		};

		auto entry = dispatchTable.find(name);
		if (entry != dispatchTable.end())
		{
			auto [name, instance] = *entry;
			return instance();
		}
		else return nullptr;

	}

	void GraphicsSystem::CreateEntryPoint()
	{
		ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(_factory.ReleaseAndGetAddressOf())));
	}

	void GraphicsSystem::PickAdapter()
	{
		return;
	}

	void GraphicsSystem::CreateDevice()
	{
		
		ThrowIfFailed(D3D11CreateDevice(
			nullptr,                          // Video adapter
			D3D_DRIVER_TYPE_HARDWARE,         // Driver type
			nullptr,                          // Software rasterizer module
			0,                                // Flags
			nullptr,                          // Feature level
			0,                                // Number of feature levels
			D3D11_SDK_VERSION,                // SDK version
			_device.ReleaseAndGetAddressOf(), // Output device
			0,                                // Output feature level
			_context.ReleaseAndGetAddressOf() // Output device context
		));

	}

	void GraphicsSystem::CreateSwapChain()
	{
		auto windowHandle = glfwGetWin32Window(reinterpret_cast<GLFWwindow*>(_window->NativeHandle()));

		DXGI_SWAP_CHAIN_DESC swapChainDescription
		{
			.BufferDesc =
			{
				.Width            = static_cast<UINT>(_outputWidth),
				.Height           = static_cast<UINT>(_outputHeight),
				.RefreshRate      = {.Numerator = 0, .Denominator = 1 },
				.Format           = DXGI_FORMAT_R8G8B8A8_UNORM,
				.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
				.Scaling          = DXGI_MODE_SCALING_UNSPECIFIED
			},
			.SampleDesc           = {.Count = 1, .Quality = 0 },
			.BufferUsage          = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT,
			.BufferCount          = 2,
			.OutputWindow         = windowHandle,
			.Windowed             = TRUE,
			.SwapEffect           = DXGI_SWAP_EFFECT_DISCARD,
			.Flags                = 0
		};

		ThrowIfFailed(_factory->CreateSwapChain(
			_device.Get(),
			&swapChainDescription, 
			_swapChain.ReleaseAndGetAddressOf()
		));

	}

	void GraphicsSystem::CreateRenderTarget()
	{

		ThrowIfFailed(_swapChain->GetBuffer(0, IID_PPV_ARGS(_renderTarget.ReleaseAndGetAddressOf())));
		
		ThrowIfFailed(_device->CreateRenderTargetView(
			_renderTarget.Get(),
			nullptr,
			_renderTargetView.ReleaseAndGetAddressOf()
		));

	}

	void GraphicsSystem::CreateDepthStencil()
	{
		CD3D11_TEXTURE2D_DESC depthStencilDescription(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			static_cast<UINT>(_outputWidth),
			static_cast<UINT>(_outputHeight),
			1, 
			1, 
			D3D11_BIND_DEPTH_STENCIL);

		ThrowIfFailed(_device->CreateTexture2D(
			&depthStencilDescription,
			nullptr, 
			_depthStencil.GetAddressOf()
		));

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription(D3D11_DSV_DIMENSION_TEXTURE2D);
		ThrowIfFailed(_device->CreateDepthStencilView(
			_depthStencil.Get(), 
			&depthStencilViewDescription, 
			_depthStencilView.ReleaseAndGetAddressOf()
		));

	}

	void GraphicsSystem::Clear()
	{
		constexpr float cornFlowerBlue[] = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };

		_context->ClearRenderTargetView(_renderTargetView.Get(), cornFlowerBlue);
		_context->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());

		CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(_outputWidth), static_cast<float>(_outputHeight));
		_context->RSSetViewports(1, &viewport);
	}

	void GraphicsSystem::Present()
	{
		ThrowIfFailed(_swapChain->Present(0, 0));
	}

}