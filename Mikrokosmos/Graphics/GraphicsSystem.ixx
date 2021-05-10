module;

#include <cmath>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#define NOMINMAX
#include <wrl/client.h>
#include <d3d11.h>

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
		float4 color;
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

	class Direct3D11Exception : public std::exception
	{
	public:
		Direct3D11Exception(HRESULT hr) : result(hr) {}

		virtual const char* what() const override
		{
			static char message[64] = {};
			sprintf_s(message, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
			return message;
		}

	private:
		HRESULT result;
	};

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw Direct3D11Exception(hr);
		}
	}

	class GraphicsSystem
	{

	public:

		template <typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		struct Description
		{
			std::string renderer = "Direct3D11";
			Window*     window   = nullptr;
		};

		GraphicsSystem(const Description& description);

		void Initialize();
		void Render();
		void Shutdown();

	private:

		std::unique_ptr<Renderer> CreateRenderer(const std::string& name);

		void CreateEntryPoint();
		void PickAdapter();
		void CreateDevice();
		void CreateSwapChain();
		void CreateRenderTarget();
		void CreatePipeline();
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void CreateConstantBuffer();
		void CreateTexture();

		void Clear();
		void Present();

	private:

		std::unique_ptr<Renderer>        _renderer;
		//std::unique_ptr<RenderDevice>  _renderDevice;
		//std::unique_ptr<DeviceContext> _deviceContext;
		//std::unique_ptr<SwapChain>     _swapChain;
		
		Window* _window;
		std::size_t _outputWidth;
		std::size_t _outputHeight;

		ComPtr<IDXGIFactory>             _factory;
		ComPtr<IDXGIAdapter>             _adapter;
		ComPtr<ID3D11Device>             _device;
		ComPtr<ID3D11DeviceContext>      _context;
									     
		ComPtr<IDXGISwapChain>           _swapChain;
		ComPtr<ID3D11Texture2D>          _renderTarget;
		ComPtr<ID3D11Texture2D>          _depthStencil;
		ComPtr<ID3D11RenderTargetView>   _renderTargetView;
		ComPtr<ID3D11DepthStencilView>   _depthStencilView;
									     
		ComPtr<ID3D11InputLayout>        _inputLayout;
		ComPtr<ID3D11Buffer>             _indexBuffer;
		ComPtr<ID3D11Buffer>             _vertexBuffer;
		ComPtr<ID3D11Buffer>             _constantBuffer;
									     
		ComPtr<ID3D11VertexShader>       _vertexShader;
		ComPtr<ID3D11PixelShader>        _pixelShader;
									     
		ConstantBuffer                   _constantBufferData;

		ComPtr<ID3D11ShaderResourceView> _textureView;
		ComPtr<ID3D11SamplerState>       _samplerState;

		float                            _angle               = 0.0f;
	};

	

}