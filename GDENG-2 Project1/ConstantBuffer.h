#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"
#include "DeviceContext.h"

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();
	bool load(void* buffer, UINT sizeBuffer);
	void update(DeviceContext* context, void* buffer);
	bool release();
	~ConstantBuffer();

private:
	ID3D11Buffer* Buffer;

private:
	friend class DeviceContext;
};

