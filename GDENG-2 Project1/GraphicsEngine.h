#pragma once
#include <d3d11.h>

class SwapChain;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();
	bool release();
	ID3D11Device* getD3Ddevice();
	D3D_FEATURE_LEVEL getFeatureLevel();
	ID3D11DeviceContext* getDeviceContext();
	~GraphicsEngine();

public:
	SwapChain* createSwapChain();

public:
	static GraphicsEngine* getInstance();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

private:
	friend class SwapChain;
};
