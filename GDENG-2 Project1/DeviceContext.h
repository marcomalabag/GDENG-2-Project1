#pragma once
#include <d3d11.h>
#include "VertexBuffer.h"

class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();
	void clearRenderTargetColor(SwapChain* swapchain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setViewportSize(UINT width, UINT height);
	void drawTriangleList(UINT vertex_count, UINT startVertexIndex);
	~DeviceContext();

private:
	ID3D11DeviceContext* Devicecontext;


	
};

