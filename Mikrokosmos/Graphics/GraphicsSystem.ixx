module;

#include <cmath>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <Mikrokosmos/Graphics/Rendering/Direct3D11/Direct3D11.h>

export module Mikrokosmos.Graphics.GraphicsSystem;

import Mikrokosmos.Graphics.Rendering;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.UI.Window;

export namespace mk
{

	struct float2
	{
		float x, y;
	};

	struct float3
	{
		float x, y, z;
	};

	struct float4
	{
		float x, y, z, w;
	};

	struct float4x4
	{
		union
		{
			struct
			{
				float _11;
				float _12;
				float _13;
				float _14;
				float _21;
				float _22;
				float _23;
				float _24;
				float _31;
				float _32;
				float _33;
				float _34;
				float _41;
				float _42;
				float _43;
				float _44;
			};
			float m[4][4];
		};
	};

	struct Vertex
	{
		float3 position;
		float3 normal;
		float2 textureCoordinates;
	};

	struct ConstantBuffer
	{
		float4x4 model;
		float4x4 view;
		float4x4 projection;
	};

	inline float4x4 MatrixRotationY(float angle) noexcept
	{

		float sinAngle = std::sin(angle);
		float cosAngle = std::cos(angle);

		float4x4 M;
		M.m[0][0] = cosAngle;
		M.m[0][1] = 0.0f;
		M.m[0][2] = -sinAngle;
		M.m[0][3] = 0.0f;

		M.m[1][0] = 0.0f;
		M.m[1][1] = 1.0f;
		M.m[1][2] = 0.0f;
		M.m[1][3] = 0.0f;

		M.m[2][0] = sinAngle;
		M.m[2][1] = 0.0f;
		M.m[2][2] = cosAngle;
		M.m[2][3] = 0.0f;

		M.m[3][0] = 0.0f;
		M.m[3][1] = 0.0f;
		M.m[3][2] = 0.0f;
		M.m[3][3] = 1.0f;
		
		return M;
	}

	std::vector<std::byte> load(std::string const& filepath)
	{
		std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);

		if (!ifs);
			//throw std::runtime_error(filepath + ": " + std::strerror(errno));

		auto end = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		auto size = std::size_t(end - ifs.tellg());

		if (size == 0) // avoid undefined behavior 
			return {};

		std::vector<std::byte> buffer(size);

		if (!ifs.read((char*)buffer.data(), buffer.size()));
			//throw std::runtime_error(filepath + ": " + std::strerror(errno));

		return buffer;
	}

	class GraphicsSystem
	{

	public:

		struct Description
		{
			std::string renderer = "Direct3D11";
			Window*     window   = nullptr;
		};

		GraphicsSystem(const Description& description);

		void Initialize();
		void Render();
		void Shutdown();

		void OnWindowResized(const Vector2u& newSize);

	private:

		std::unique_ptr<Renderer> CreateRenderer(const std::string& name);

		void CreateEntryPoint();
		void PickAdapter();
		void CreateDevice();
		void CreateTargetSizeDependentResources();
		void CreatePipeline();
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void CreateConstantBuffer();
		void CreateTexture();

		void Present();

	private:

		std::unique_ptr<Renderer>        _renderer;
		//std::unique_ptr<Device>        _renderDevice;
		//std::unique_ptr<DeviceContext> _deviceContext;
		//std::unique_ptr<SwapChain>     _swapChain;
		
		Window* _window;
		std::size_t _outputWidth;
		std::size_t _outputHeight;

		Microsoft::WRL::ComPtr<IDXGIFactory2>            _factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter>             _adapter;
		Microsoft::WRL::ComPtr<ID3D11Device1>            _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1>     _context;
									     
		Microsoft::WRL::ComPtr<IDXGISwapChain1>          _swapChain;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>          _renderTarget;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>          _depthStencil;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>   _renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>   _depthStencilView;
									     
		Microsoft::WRL::ComPtr<ID3D11InputLayout>        _inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>             _indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>             _vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>             _constantBuffer;
									     
		Microsoft::WRL::ComPtr<ID3D11VertexShader>       _vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>        _pixelShader;
									     
		ConstantBuffer                                   _constantBufferData;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _textureView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState>       _samplerState;

		float                                            _angle               = 0.0f; // This value will be used to animate the cube by rotating it every frame.
	};

	

}