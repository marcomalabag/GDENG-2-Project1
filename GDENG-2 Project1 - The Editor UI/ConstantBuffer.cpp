#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer()
{
}

bool ConstantBuffer::load(void* buffer, UINT sizeBuffer)
{
	if(this->Buffer)
	{
		this->Buffer->Release();
	}

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = sizeBuffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(GraphicsEngine::getInstance()->getD3Ddevice()->CreateBuffer(&buff_desc, &init_data, &this->Buffer)))
	{
		std::cout << "Failed to create constant buffer";
		return false;
	}

	return true;
}

void ConstantBuffer::update(DeviceContext* context, void* buffer)
{
	context->Devicecontext->UpdateSubresource(this->Buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::release()
{
	if(this->Buffer)
	{
		this->Buffer->Release();
		delete this;
	}

	return true;
}

ConstantBuffer::~ConstantBuffer()
{
}
