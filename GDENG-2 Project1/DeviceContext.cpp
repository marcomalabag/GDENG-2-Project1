#include "DeviceContext.h"
#include "SwapChain.h"	

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context)
{
	this->Devicecontext = device_context;
}

bool DeviceContext::release()
{
	this->Devicecontext->Release();
	delete this;
	return true;
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swapchain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };
	this->Devicecontext->ClearRenderTargetView(swapchain->RenderTargetView, clear_color);
	return true;
}

DeviceContext::~DeviceContext()
{
}
