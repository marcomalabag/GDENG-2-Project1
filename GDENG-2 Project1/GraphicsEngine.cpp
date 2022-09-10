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

	if (this->pixelshader)
	{
		this->pixelshader->Release();
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
	return new VertexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	class VertexShader* vs = new class VertexShader();

	if(!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size)) {
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* errorBlob = nullptr;
	if(!SUCCEEDED(D3DCompileFromFile(Filename, nullptr, nullptr, EntryPointName, "vs_5_0", 0, 0, &this->m_blob, &errorBlob)))
	{
		if(errorBlob)
		{
			std::cout<<"Faied to compile vertex shader";
			errorBlob->Release();
			return false;
		}
	}

	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(Filename, nullptr, nullptr, EntryPointName, "ps_5_0", 0, 0, &this->m_blob, &errorBlob)))
	{
		if (errorBlob)
		{
			std::cout << "Faied to compile pixel shader";
			errorBlob->Release();
			return false;
		}
	}

	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if(this->m_blob)
	{
		this->m_blob->Release();
	}
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}



GraphicsEngine* GraphicsEngine::getInstance()
{
	static GraphicsEngine engine;
	return &engine;
}