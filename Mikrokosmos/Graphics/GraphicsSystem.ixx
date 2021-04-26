module;

#include <memory>
#include <string>

#define NOMINMAX
#include <wrl/client.h>
#include <d3d11.h>

export module Mikrokosmos.Graphics.GraphicsSystem;

import Mikrokosmos.Graphics.Rendering;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.UI.Window;

export namespace mk
{

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
		void CreateDepthStencil();

		void Clear();
		void Present();

	private:

		std::unique_ptr<Renderer>        _renderer;
		//std::unique_ptr<RenderDevice>  _renderDevice;
		//std::unique_ptr<DeviceContext> _deviceContext;
		//std::unique_ptr<SwapChain>     _swapChain;
		Window* _window;

		ComPtr<IDXGIFactory>           _factory;
		ComPtr<IDXGIAdapter>           _adapter;
		ComPtr<ID3D11Device>           _device;
		ComPtr<ID3D11DeviceContext>    _context;
		ComPtr<IDXGISwapChain>         _swapChain;

		ComPtr<ID3D11Texture2D>        _renderTarget;
		ComPtr<ID3D11Texture2D>        _depthStencil;
		ComPtr<ID3D11RenderTargetView> _renderTargetView;
		ComPtr<ID3D11DepthStencilView> _depthStencilView;

		std::size_t _outputWidth;
		std::size_t _outputHeight;

	};

	

}