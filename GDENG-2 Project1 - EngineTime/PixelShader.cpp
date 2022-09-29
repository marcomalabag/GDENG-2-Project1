#include "PixelShader.h"

PixelShader::PixelShader()
{
}

bool PixelShader::init(const void* shader_byte, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::getInstance()->getD3Ddevice()->CreatePixelShader(shader_byte, byte_code_size,
		nullptr, &this->pixelshader))) {
		std::cout << "Failed to create pixel shader";
		return false;
	}
	return true;
}

void PixelShader::release()
{
	this->pixelshader->Release();
	delete this;
}

PixelShader::~PixelShader()
{
}


