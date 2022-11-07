#include "VertexShader.h"

VertexShader::VertexShader()
{
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if(!SUCCEEDED(GraphicsEngine::getInstance()->getD3Ddevice()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &this->vertexShader)))
	{
		std::cout << "Failed to create vertex shader";
		return false;		
	}
	return true;
}

bool VertexShader::release()
{
	this->vertexShader;
	delete this;
	return true;
}

VertexShader::~VertexShader()
{
}


