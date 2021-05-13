#pragma once

#define NOMINMAX

#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>

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
