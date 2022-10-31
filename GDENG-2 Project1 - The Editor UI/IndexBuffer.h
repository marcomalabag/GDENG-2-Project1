#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"
#include <iostream>
#include "DeviceContext.h"

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();
	bool load(void* list_indices, UINT size_list);
	UINT getSizeIndexList();
	bool release();
	~IndexBuffer();

private:
	UINT SizeList;

private:
	ID3D11Buffer* m_buffer;

private:
	friend class DeviceContext;


};

