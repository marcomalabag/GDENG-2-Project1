#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"


class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class IndexBuffer;

class GraphicsEngine
{
public:
	
	bool init();
	bool release();
	ID3D11Device* getD3Ddevice();
	D3D_FEATURE_LEVEL getFeatureLevel();
	IDXGIFactory* getFactory();
	
	

public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();
	IndexBuffer* createIndexBuffer();
	ConstantBuffer* createConstantBuffer();
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	

public:
	bool compileVertexShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();


	

public:
	static GraphicsEngine* getInstance();
	static void initialize();
	static void destroy();

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&){};
	GraphicsEngine&operator=(GraphicsEngine const&){};

private:
	static GraphicsEngine* sharedInstance;

private:
	DeviceContext* m_imm_device_context;

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

private:
	ID3DBlob* m_blob = nullptr;
	ID3DBlob* VertexShaderBlob = nullptr;
	ID3DBlob* PixelShaderBlob = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11PixelShader* pixelshader = nullptr;


private:
	friend class SwapChain;
	friend class ConstantBuffer;
	friend class IndexBuffer;
};
