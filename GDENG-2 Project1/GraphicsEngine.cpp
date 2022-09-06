#include "GraphicsEngine.h"
#include "SwapChain.h"
#include <d3dcompiler.h>


GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT result = 0;
	
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL,
			feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level,
			&this->m_imm_context);

		if (SUCCEEDED(result))
		{
			break;
			driver_type_index++;
		}
	}

	if (FAILED(result))
	{
		return false;
	}

	this->m_imm_device_context = new DeviceContext(this->m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**) &m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	

	return true;
}

bool GraphicsEngine::release()
{
	if(this->VertexShader)
	{
		this->VertexShader->Release();
	}

	if (this->PixelShader)
	{
		this->PixelShader->Release();
	}

	if(this->VertexShaderBlob)
	{
		this->VertexShaderBlob->Release();
	}

	if (this->PixelShaderBlob)
	{
		this->PixelShaderBlob->Release();
	}

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	
	this->m_imm_device_context->release();
	m_d3d_device->Release();
	return true;
}

ID3D11Device* GraphicsEngine::getD3Ddevice()
{
	return this->m_d3d_device;
}

D3D_FEATURE_LEVEL GraphicsEngine::getFeatureLevel()
{
	return this->m_feature_level;
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

bool GraphicsEngine::createShaders()
{
	ID3DBlob* errorBlob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &this->VertexShaderBlob, &errorBlob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &this->PixelShaderBlob, &errorBlob);
	this->m_d3d_device->CreateVertexShader(this->VertexShaderBlob->GetBufferPointer(), this->VertexShaderBlob->GetBufferSize(), nullptr, &this->VertexShader);
	this->m_d3d_device->CreatePixelShader(this->PixelShaderBlob->GetBufferPointer(), this->PixelShaderBlob->GetBufferSize(), nullptr, &this->PixelShader);
	return true;
}

bool GraphicsEngine::setShaders()
{
	this->m_imm_context->VSSetShader(this->VertexShader, nullptr, 0);
	this->m_imm_context->PSSetShader(this->PixelShader, nullptr, 0);
	return true;
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->VertexShaderBlob->GetBufferPointer();
	*size = (UINT)this->VertexShaderBlob->GetBufferSize();
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	static GraphicsEngine engine;
	return &engine;
}