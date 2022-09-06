#pragma once
#include <d3d11.h>

class SwapChain;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();
	bool clearRenderTargetColor(SwapChain* swapchain, float red, float green, float blue, float alpha);
	~DeviceContext();

private:
	ID3D11DeviceContext* Devicecontext;
};

