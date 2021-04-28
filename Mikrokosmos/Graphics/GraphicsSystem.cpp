module;
#include <iostream>
#include <functional>
#include <map>
#include <memory>

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h> // TODO: remove.

module Mikrokosmos.Graphics.GraphicsSystem;

import Mikrokosmos.Graphics.Rendering.Direct3D11Renderer;

namespace mk
{

	struct float3
	{
		float x, y, z;
	};

	struct float4
	{
		float x, y, z, w;
	};

	struct Vertex
	{
		float3 Position;
		float4 Normal;
	};

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
				setupDebugMessenger();
						createSurface();
						pickPhysicalDevice();
						createLogicalDevice();
						createSwapChain();
				createImageViews();
				createRenderPass();
				createDescriptorSetLayout();
						createGraphicsPipeline();
				createCommandPool();
				createDepthResources();
				createFramebuffers();
				createTextureImage();
				createTextureImageView();
				createTextureSampler();
				loadModel();
						createVertexBuffer();
						createIndexBuffer();
				createUniformBuffers();
				createDescriptorPool();
				createDescriptorSets();
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
		CreatePipeline();
		CreateVertexBuffer();
		CreateIndexBuffer();
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
		ThrowIfFailed(
			CreateDXGIFactory(
				IID_PPV_ARGS(_factory.ReleaseAndGetAddressOf())
			)
		);
	}

	void GraphicsSystem::PickAdapter()
	{
		return;
	}

	void GraphicsSystem::CreateDevice()
	{
		UINT creationFlags = 0;

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_1
		};

		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		ThrowIfFailed(
			D3D11CreateDevice(
				nullptr,                  // Video adapter
				D3D_DRIVER_TYPE_HARDWARE, // Driver type
				nullptr,                  // Software rasterizer module
				creationFlags,            // Flags
				featureLevels,            // Feature level
				6,                        // Number of feature levels
				D3D11_SDK_VERSION,        // SDK version
				&device,                  // Output device
				0,                        // Output feature level
				&context                  // Output device context
			)
		);

		ThrowIfFailed(device.As(&_device));
		ThrowIfFailed(context.As(&_context));

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

		ThrowIfFailed(
			_factory->CreateSwapChain(
				_device.Get(),
				&swapChainDescription, 
				&_swapChain
			)
		);

	}

	void GraphicsSystem::CreateRenderTarget()
	{

		ThrowIfFailed(_swapChain->GetBuffer(0, IID_PPV_ARGS(_renderTarget.GetAddressOf())));
		
		ThrowIfFailed(
			_device->CreateRenderTargetView(
				_renderTarget.Get(),
				nullptr,
				&_renderTargetView
			)
		);

		/*CD3D11_TEXTURE2D_DESC depthStencilDescription(
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
		));*/

		D3D11_VIEWPORT viewport
		{
			.TopLeftX = 0.0f,
			.TopLeftY = 0.0f,
			.Width    = static_cast<float>(_outputWidth),
			.Height   = static_cast<float>(_outputHeight),
			.MinDepth = D3D11_MIN_DEPTH,
			.MaxDepth = D3D11_MAX_DEPTH
		};

		_context->RSSetViewports(1, &viewport);

	}

	void GraphicsSystem::CreatePipeline()
	{
		ComPtr<ID3DBlob> vertexShaderCode;
		ComPtr<ID3DBlob> pixelShaderCode;
		
		ThrowIfFailed(
			D3DCompileFromFile(
				L"Simple.hlsl",
				nullptr,
				nullptr,
				"VSMain",
				"vs_4_0",
				0,
				0,
				&vertexShaderCode,
				nullptr
			)
		);

		ThrowIfFailed(
			_device->CreateVertexShader(
				vertexShaderCode->GetBufferPointer(),
				vertexShaderCode->GetBufferSize(),
				nullptr,
				&_vertexShader
			)
		);
		
		ThrowIfFailed(
			D3DCompileFromFile(
				L"Simple.hlsl", 
				nullptr,
				nullptr,
				"PSMain", 
				"ps_4_0", 
				0, 
				0, 
				&pixelShaderCode,
				nullptr
			)
		);

		ThrowIfFailed(
			_device->CreatePixelShader(
				pixelShaderCode->GetBufferPointer(),
				pixelShaderCode->GetBufferSize(),
				nullptr, 
				&_pixelShader
			)
		);

		const D3D11_INPUT_ELEMENT_DESC inputElementDescription[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		ThrowIfFailed(
			_device->CreateInputLayout(
				inputElementDescription, 
				2, 
				vertexShaderCode->GetBufferPointer(), 
				vertexShaderCode->GetBufferSize(), 
				&_inputLayout
			)
		);

	}

	void GraphicsSystem::CreateVertexBuffer()
	{

		Vertex triangleVertices[] =
		{
			{ { +0.0f, +0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { +0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
		};

		D3D11_BUFFER_DESC vertexBufferDescription
		{
			.ByteWidth           = 3 * sizeof(Vertex),
			.Usage               = D3D11_USAGE_DEFAULT,
			.BindFlags           = D3D11_BIND_VERTEX_BUFFER,
			.CPUAccessFlags      = 0,
			.MiscFlags           = 0,
			.StructureByteStride = 0
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData
		{
			.pSysMem          = triangleVertices,
			.SysMemPitch      = 0,
			.SysMemSlicePitch = 0
		};
		
		ThrowIfFailed(
			_device->CreateBuffer(
				&vertexBufferDescription, 
				&vertexBufferData, 
				&_vertexBuffer
			)
		);
	}

	void GraphicsSystem::CreateIndexBuffer()
	{

		unsigned short triangleIndices[] =
		{
		   0, 1, 2
		};

		D3D11_BUFFER_DESC indexBufferDescription
		{
			.ByteWidth		     = 3 * sizeof(unsigned short),
			.Usage			     = D3D11_USAGE_DEFAULT,
			.BindFlags		     = D3D11_BIND_INDEX_BUFFER,
			.CPUAccessFlags	     = 0,
			.MiscFlags		     = 0,
			.StructureByteStride = 0
		};

		D3D11_SUBRESOURCE_DATA indexBufferData
		{
			.pSysMem          = triangleIndices,
			.SysMemPitch      = 0,
			.SysMemSlicePitch = 0
		};

		ThrowIfFailed(
			_device->CreateBuffer(
				&indexBufferDescription,
				&indexBufferData,
				&_indexBuffer
			)
		);
	}

	void GraphicsSystem::Render()
	{
		_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
		
		const float clearColor[] = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };

		_context->ClearRenderTargetView(_renderTargetView.Get(), clearColor);
		//_context->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		_context->IASetInputLayout(_inputLayout.Get());

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		_context->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_context->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		_context->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_context->PSSetShader(_pixelShader.Get(),  nullptr, 0);

		_context->DrawIndexed(3, 0, 0);

		ThrowIfFailed(_swapChain->Present(1, 0));
	}

}