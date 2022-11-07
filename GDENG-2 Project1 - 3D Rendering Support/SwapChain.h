#pragma once
#include <d3d11.h>

#include "DeviceContext.h"

class DeviceContext;
class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();
	bool release();
	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11DepthStencilView* DepthView;

private:
	friend class DeviceContext;
};

