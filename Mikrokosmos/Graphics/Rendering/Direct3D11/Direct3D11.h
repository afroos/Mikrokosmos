#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include <dxgi1_6.h>

#include <d3dcompiler.h>


template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

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
