#pragma once
#include "Resource.h"
#include <d3d11.h>
#include "DeviceContext.h"

class DevviceContext;
class Texture: public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();

private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* shaderResView = nullptr;

private:
	friend class DeviceContext;
};

