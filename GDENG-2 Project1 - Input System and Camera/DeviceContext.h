#pragma once
#include <d3d11.h>
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"

class SwapChain;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();
	void clearRenderTargetColor(SwapChain* swapchain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);
	
	void setViewportSize(UINT width, UINT height);
	void drawTriangleList(UINT vertex_count, UINT startVertexIndex);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT startVertexIndex);
	~DeviceContext();

public:
	void setVertexShader(VertexShader* vertex_shader);
	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer);

	void setPixelShader(PixelShader* pixel_shader);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer);

private:
	ID3D11DeviceContext* Devicecontext;

private:
	friend class ConstantBuffer;


	
};

