#pragma once
#include <d3d11.h>
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class SwapChain;
class VertexBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();
	void clearRenderTargetColor(SwapChain* swapchain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setViewportSize(UINT width, UINT height);
	void drawTriangleList(UINT vertex_count, UINT startVertexIndex);
	void drawTriangleStrip(UINT vertex_count, UINT startVertexIndex);
	~DeviceContext();

public:
	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

private:
	ID3D11DeviceContext* Devicecontext;


	
};

