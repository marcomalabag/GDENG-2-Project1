#pragma once
#include <d3d11.h>
#include "DeviceContext.h"

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();
	bool release();
	ID3D11Device* getD3Ddevice();
	D3D_FEATURE_LEVEL getFeatureLevel();
	DeviceContext* getImmediateDeviceContext();
	~GraphicsEngine();

public:
	SwapChain* createSwapChain();

public:
	static GraphicsEngine* getInstance();

private:
	DeviceContext* m_imm_device_context;

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

private:
	friend class SwapChain;
};
