#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	this->Layout = 0;
	this->Buffer = 0;
}

ID3D11Buffer* VertexBuffer::getBuffer()
{
	return this->Buffer;
}

ID3D11InputLayout* VertexBuffer::getLayout()
{
	return this->Layout;
}

UINT VertexBuffer::getSizeVertexBuffer()
{
	return this->sizeVertexBuffer;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->sizeVertexList;
}

bool VertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{

	if(this->Buffer)
	{
		this->Buffer->Release();
	}

	if(this->Layout)
	{
		this->Layout->Release();
	}


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->sizeVertexBuffer = size_vertex;
	this->sizeVertexList = size_list;


	if(FAILED(GraphicsEngine::getInstance()->getD3Ddevice()->CreateBuffer(&buff_desc, &init_data, &this->Buffer)))
	{
		std::cout<<"Failed to create vertex buffer";
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			12,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{ "COLOR",
			1,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			24,
			D3D11_INPUT_PER_VERTEX_DATA ,
			0
		}
	};

	UINT size_layout = ARRAYSIZE(layout);


	if(FAILED(GraphicsEngine::getInstance()->getD3Ddevice()->CreateInputLayout(layout, size_layout,
		shader_byte_code, size_byte_shader, &this->Layout)))
	{
		std::cout << "Failed to create input layout";
		return false;
	}



	return true;
}

bool VertexBuffer::release()
{
	this->Layout->Release();
	this->Buffer->Release();
	delete this;
	return true;
}

VertexBuffer::~VertexBuffer()
{
}


