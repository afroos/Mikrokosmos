module;
#include <iostream>
#include <functional>
#include <map>
#include <memory>

#include <Mikrokosmos/Graphics/Rendering/Direct3D11/Direct3D11.h>

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

		//_device = _renderer->CreateDevice(Device::Description{});

		//_deviceContext = _renderer->CreateDeviceContext(DeviceContext::Description{});

		//_swapChain = _renderer->CreateSwapChain({ .window = description.window });

	}

	void GraphicsSystem::Initialize()
	{
		//_renderer->Initialize();

		CreateEntryPoint();
		PickAdapter();
		CreateDevice();
		CreateTargetSizeDependentResources();
		CreatePipeline();
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateConstantBuffer();
		CreateTexture();
	}

	void GraphicsSystem::Shutdown()
	{
		//_renderer->Shutdown();
	}

	void GraphicsSystem::OnWindowResized(const Vector2u& newSize)
	{
		_outputWidth      = newSize.X();
		_outputHeight     = newSize.Y();
		_renderTargetView = nullptr;
		_depthStencilView = nullptr;
		CreateTargetSizeDependentResources();
	}

	std::unique_ptr<Renderer> GraphicsSystem::CreateRenderer(const std::string& name)
	{
		static std::map<
			std::string, 
			std::function<std::unique_ptr<Renderer>()>> dispatchTable
		{
			{ "Direct3D11", []() { return std::make_unique<Direct3D11Renderer>(); } }
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
			CreateDXGIFactory1(
				IID_PPV_ARGS(_factory.ReleaseAndGetAddressOf())
			)
		);
	}

	void GraphicsSystem::PickAdapter()
	{

	}

	void GraphicsSystem::CreateDevice()
	{
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		#if defined(DEBUG)
				// If the project is in a debug build, enable debugging via SDK Layers with this flag.
				creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_1
		};

		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

		ThrowIfFailed(
			D3D11CreateDevice(
				nullptr,                  // Video adapter
				D3D_DRIVER_TYPE_HARDWARE, // Driver type
				nullptr,                  // Software rasterizer module
				creationFlags,            // Flags
				featureLevels,            // Feature level
				ARRAYSIZE(featureLevels), // Number of feature levels
				D3D11_SDK_VERSION,        // SDK version
				&device,                  // Output device
				nullptr,                  // Output feature level
				&context                  // Output device context
			)
		);

		// Retrieve the Direct3D 11.1 interfaces.
		ThrowIfFailed(device.As(&_device));
		ThrowIfFailed(context.As(&_context));

	}

	void GraphicsSystem::CreateTargetSizeDependentResources()
	{
		if (_swapChain != nullptr)
		{
			// If the swap chain already exists, resize it.
			ThrowIfFailed(
				_swapChain->ResizeBuffers(
					2,
					0,
					0,
					DXGI_FORMAT_R8G8B8A8_UNORM,
					0
				)
			);
		}
		else
		{
			// If the swap chain does not exist, create it.

			DXGI_SWAP_CHAIN_DESC1 swapChainDescription
			{
				.Width = static_cast<UINT>(_outputWidth),
				.Height = static_cast<UINT>(_outputHeight),
				.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
				.Stereo = false,
				.SampleDesc = {.Count = 1, .Quality = 0 },
				.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
				.BufferCount = 2,
				.Scaling = DXGI_SCALING_NONE,
				.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
				.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
				.Flags = 0
			};

			// Once the swap chain description is configured, it must be
			// created on the same adapter as the existing D3D Device.

			// First, retrieve the underlying DXGI Device from the D3D Device.
			Microsoft::WRL::ComPtr<IDXGIDevice2> dxgiDevice;
			ThrowIfFailed(
				_device.As(&dxgiDevice)
			);

			// Ensure that DXGI does not queue more than one frame at a time. This both reduces
			// latency and ensures that the application will only render after each VSync, minimizing
			// power consumption.
			ThrowIfFailed(
				dxgiDevice->SetMaximumFrameLatency(1)
			);

			// Next, get the parent factory from the DXGI Device.
			Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
			ThrowIfFailed(
				dxgiDevice->GetAdapter(&dxgiAdapter)
			);

			Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
			ThrowIfFailed(
				dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
			);

			// Finally, create the swap chain.
			ThrowIfFailed(
				dxgiFactory->CreateSwapChainForHwnd(
					_device.Get(),
					glfwGetWin32Window(reinterpret_cast<GLFWwindow*>(_window->NativeHandle())),
					&swapChainDescription, 
					nullptr,
					nullptr,
					&_swapChain
				)
			);

		}

		// Once the swap chain is created, create a render target view.  This will
		// allow Direct3D to render graphics to the window.
		ThrowIfFailed(
			_swapChain->GetBuffer(
				0,
				IID_PPV_ARGS(&_renderTarget)
			)
		);

		ThrowIfFailed(
			_device->CreateRenderTargetView(
				_renderTarget.Get(),
				nullptr,
				&_renderTargetView
			)
		);

		// Once the render target view is created, create a depth stencil view.  This
		// allows Direct3D to efficiently render objects closer to the camera in front
		// of objects further from the camera.
		D3D11_TEXTURE2D_DESC depthStencilDescription
		{
			.Width = static_cast<UINT>(_outputWidth),
			.Height = static_cast<UINT>(_outputHeight),
			.MipLevels = 1,
			.ArraySize = 1,
			.Format = DXGI_FORMAT_D24_UNORM_S8_UINT,
			.SampleDesc = {.Count = 1, .Quality = 0},
			.Usage = D3D11_USAGE_DEFAULT,
			.BindFlags = D3D11_BIND_DEPTH_STENCIL,
			.CPUAccessFlags = 0,
			.MiscFlags = 0
		};

		ThrowIfFailed(
			_device->CreateTexture2D(
				&depthStencilDescription,
				nullptr,
				&_depthStencil
			)
		);

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription
		{
			.Format = depthStencilDescription.Format,
			.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D,
			.Flags = 0,
			.Texture2D = {.MipSlice = 0 }
		};

		ThrowIfFailed(
			_device->CreateDepthStencilView(
				_depthStencil.Get(),
				&depthStencilViewDescription,
				&_depthStencilView
			)
		);
		
		// Finally, update the constant buffer perspective projection parameters
		// to account for the size of the application window.  In this sample,
		// the parameters are fixed to a 70-degree field of view, with a depth
		// range of 0.01 to 100.
		float xScale = 1.42814801f;
		float yScale = 1.42814801f;

		if (_outputWidth > _outputHeight)
		{
			xScale = yScale *
				static_cast<float>(_outputHeight) /
				static_cast<float>(_outputWidth);
		}
		else
		{
			yScale = xScale *
				static_cast<float>(_outputWidth) /
				static_cast<float>(_outputHeight);
		}

		_constantBufferData.projection =
		{
			xScale, 0.0f,    0.0f,   0.0f,
			0.0f,   yScale,  0.0f,   0.0f,
			0.0f,   0.0f,   -1.0f,  -0.01f,
			0.0f,   0.0f,   -1.0f,   0.0f
		};

	}

	void GraphicsSystem::CreatePipeline()
	{
		Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderCode;
		
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

		// Create an input layout that matches the layout defined in the vertex shader code.
		const D3D11_INPUT_ELEMENT_DESC inputElementDescription[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		ThrowIfFailed(
			_device->CreateInputLayout(
				inputElementDescription,
				3,
				vertexShaderCode->GetBufferPointer(),
				vertexShaderCode->GetBufferSize(),
				&_inputLayout
			)
		);

		Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderCode;
		
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

	}

	void GraphicsSystem::CreateVertexBuffer()
	{

		// In the array below, which will be used to initialize the cube vertex buffers,
		// multiple vertices are used for each corner to allow different normal vectors and
		// texture coordinates to be defined for each face.
		Vertex vertices[] =
		{
			{ {-0.5f, 0.5f, -0.5f }, {0.0f, 1.0f, 0.0f},  {0.0f, 0.0f} }, // +Y {top face}
			{ {0.5f, 0.5f, -0.5f  }, {0.0f, 1.0f, 0.0f},  {1.0f, 0.0f} },
			{ {0.5f, 0.5f,  0.5f  }, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f} },
			{ {-0.5f, 0.5f,  0.5f }, {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f} },

			{ {-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} }, // -Y {bottom face}
			{ {0.5f, -0.5f,  0.5f }, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} },
			{ {0.5f, -0.5f, -0.5f }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
			{ {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },

			{ {0.5f,  0.5f,  0.5f }, {1.0f, 0.0f, 0.0f},  {0.0f, 0.0f} }, // +X {right face}
			{ {0.5f,  0.5f, -0.5f }, {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f} },
			{ {0.5f, -0.5f, -0.5f }, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f} },
			{ {0.5f, -0.5f,  0.5f }, {1.0f, 0.0f, 0.0f},  {0.0f, 1.0f} },

			{ {-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }, // -X {left face}
			{ {-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
			{ {-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
			{ {-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },

			{ {-0.5f,  0.5f, 0.5f }, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f} }, // +Z {front face}
			{ {0.5f,  0.5f, 0.5f  }, {0.0f, 0.0f, 1.0f},  {1.0f, 0.0f} },
			{ {0.5f, -0.5f, 0.5f  }, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f} },
			{ {-0.5f, -0.5f, 0.5f }, {0.0f, 0.0f, 1.0f},  {0.0f, 1.0f} },

			{ {0.5f,  0.5f, -0.5f }, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} }, // -Z {back face}
			{ {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} },
			{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} },
			{ {0.5f, -0.5f, -0.5f }, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} },
		};

		D3D11_BUFFER_DESC vertexBufferDescription
		{
			.ByteWidth           = ARRAYSIZE(vertices) * sizeof(Vertex),
			.Usage               = D3D11_USAGE_DEFAULT,
			.BindFlags           = D3D11_BIND_VERTEX_BUFFER,
			.CPUAccessFlags      = 0,
			.MiscFlags           = 0,
			.StructureByteStride = 0
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData
		{
			.pSysMem          = vertices,
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

		unsigned short indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};

		D3D11_BUFFER_DESC indexBufferDescription
		{
			.ByteWidth		     = ARRAYSIZE(indices) * sizeof(unsigned short),
			.Usage			     = D3D11_USAGE_DEFAULT,
			.BindFlags		     = D3D11_BIND_INDEX_BUFFER,
			.CPUAccessFlags	     = 0,
			.MiscFlags		     = 0,
			.StructureByteStride = 0
		};

		D3D11_SUBRESOURCE_DATA indexBufferData
		{
			.pSysMem          = indices,
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

	void GraphicsSystem::CreateConstantBuffer()
	{

		// Create a constant buffer for passing model, view, and projection matrices
		// to the vertex shader.
		D3D11_BUFFER_DESC constantBufferDescription
		{
			.ByteWidth           = sizeof(_constantBufferData),
			.Usage               = D3D11_USAGE_DEFAULT,
			.BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
			.CPUAccessFlags      = 0,
			.MiscFlags           = 0,
			.StructureByteStride = 0
		};
		
		ThrowIfFailed(
			_device->CreateBuffer(
				&constantBufferDescription,
				nullptr,
				&_constantBuffer
			)
		);

		// Specify the view transform corresponding to a camera position of
		// X = 0, Y = 1, Z = 2.
		_constantBufferData.view = 
		{
			-1.00000000f, 0.00000000f,  0.00000000f,  0.00000000f,
			 0.00000000f, 0.89442718f,  0.44721359f,  0.00000000f,
			 0.00000000f, 0.44721359f, -0.89442718f, -2.23606800f,
			 0.00000000f, 0.00000000f,  0.00000000f,  1.00000000f
		};
	}

	void GraphicsSystem::CreateTexture()
	{
		// Load the raw texture data from disk and construct a subresource description that references it.
		auto textureData = load("texturedata.bin");

		D3D11_SUBRESOURCE_DATA textureSubresourceData =
		{
			.pSysMem          = textureData.data(),
			.SysMemPitch      = 1024,
			.SysMemSlicePitch = 0
		};

		D3D11_TEXTURE2D_DESC textureDescription
		{
			.Width          = 256,
			.Height         = 256,
			.MipLevels	    = 1,
			.ArraySize	    = 1,
			.Format         = DXGI_FORMAT_R8G8B8A8_UNORM,
			.SampleDesc	    = {.Count = 1, .Quality = 0 },
			.Usage          = D3D11_USAGE_DEFAULT,
			.BindFlags	    = D3D11_BIND_SHADER_RESOURCE,
			.CPUAccessFlags = 0,
			.MiscFlags	    = 0,
		};

		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(
			_device->CreateTexture2D(
				&textureDescription,
				&textureSubresourceData,
				&texture
			)
		);

		D3D11_SHADER_RESOURCE_VIEW_DESC textureViewDescription
		{
			.Format        = textureDescription.Format,
			.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D,
			.Texture2D     = { .MostDetailedMip = 0, .MipLevels = textureDescription.MipLevels }
		};

		ThrowIfFailed(
			_device->CreateShaderResourceView(
				texture.Get(),
				&textureViewDescription,
				&_textureView
			)
		);

		D3D11_SAMPLER_DESC samplerDescription
		{
			.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP,
			.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP,
			.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP,
			.MipLODBias     = 0.0f,
			.MaxAnisotropy  = 0,
			.ComparisonFunc = D3D11_COMPARISON_NEVER,
			.BorderColor    = {0.0f, 0.0f, 0.0f, 0.0f},
			.MinLOD         = 0,
			.MaxLOD         = D3D11_FLOAT32_MAX
		};

		ThrowIfFailed(
			_device->CreateSamplerState(
				&samplerDescription,
				&_samplerState
			)
		);
	}

	void GraphicsSystem::Render()
	{
		// Update the constant buffer to rotate the cube model.
		_constantBufferData.model = MatrixRotationY(-_angle);
		
		_angle += 0.0001f;

		_context->UpdateSubresource(
			_constantBuffer.Get(),
			0,
			nullptr,
			&_constantBufferData,
			0,
			0
		);
		
		// Clear the render target to a solid color, and reset the depth stencil.
		const float clearColor[] = { 0.098f, 0.098f, 0.439f, 1.000f };

		_context->ClearRenderTargetView(
			_renderTargetView.Get(), 
			clearColor
		);
		
		_context->ClearDepthStencilView(
			_depthStencilView.Get(), 
			D3D11_CLEAR_DEPTH, 
			1.0f, 
			0
		);

		// Specify the render target and depth stencil we created as the output target.
		_context->OMSetRenderTargets(
			1,
			_renderTargetView.GetAddressOf(),
			_depthStencilView.Get()
		);

		// Specify that the viewport, which describes what portion of the window to 
		// draw to, should cover the entire window.
		D3D11_VIEWPORT viewport
		{
			.TopLeftX = 0.0f,
			.TopLeftY = 0.0f,
			.Width = static_cast<float>(_outputWidth),
			.Height = static_cast<float>(_outputHeight),
			.MinDepth = D3D11_MIN_DEPTH,
			.MaxDepth = D3D11_MAX_DEPTH
		};

		_context->RSSetViewports(1, &viewport);

		_context->IASetInputLayout(_inputLayout.Get());

		// Set the vertex and index buffers, and specify the way they define geometry.
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		_context->IASetVertexBuffers(
			0, 
			1, 
			_vertexBuffer.GetAddressOf(), 
			&stride, 
			&offset
		);

		_context->IASetIndexBuffer(
			_indexBuffer.Get(), 
			DXGI_FORMAT_R16_UINT, 
			0
		);

		_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// Set the vertex and pixel shader stage state.
		_context->VSSetShader(
			_vertexShader.Get(), 
			nullptr, 
			0
		);

		_context->VSSetConstantBuffers(
			0,
			1,
			_constantBuffer.GetAddressOf()
		);

		_context->PSSetShader(
			_pixelShader.Get(),  
			nullptr, 
			0
		);

		_context->PSSetShaderResources(
			0,
			1,
			_textureView.GetAddressOf()
		);

		_context->PSSetSamplers(
			0,
			1,
			_samplerState.GetAddressOf()
		);

		_context->DrawIndexed(
			36, 
			0, 
			0
		);

		ThrowIfFailed(_swapChain->Present(1, 0));
	}

}