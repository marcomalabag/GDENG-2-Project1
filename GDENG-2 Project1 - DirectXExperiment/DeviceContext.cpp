#include "DeviceContext.h"
#include "SwapChain.h"	

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context)
{
	this->Devicecontext = device_context;
}

bool DeviceContext::release()
{
	this->Devicecontext->Release();
	delete this;
	return true;
}

void DeviceContext::clearRenderTargetColor(SwapChain* swapchain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };
	this->Devicecontext->ClearRenderTargetView(swapchain->RenderTargetView, clear_color);
	this->Devicecontext->OMSetRenderTargets(1, &swapchain->RenderTargetView, NULL);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->getSizeVertexBuffer();
	UINT offset = 0;

	this->Devicecontext->IASetVertexBuffers(0, 1, &vertex_buffer->Buffer, &stride, &offset);
	this->Devicecontext->IASetInputLayout(vertex_buffer->Layout);
}

void DeviceContext::setVertexShader(VertexShader* vertex_shader)
{
	this->Devicecontext->VSSetShader(vertex_shader->vertexShader, nullptr, 0);
}

void DeviceContext::setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer)
{
	this->Devicecontext->VSSetConstantBuffers(0, 1, &constant_buffer->Buffer);
}

void DeviceContext::setPixelShader(PixelShader* pixel_shader)
{
	this->Devicecontext->PSSetShader(pixel_shader->pixelshader, nullptr, 0);
}

void DeviceContext::setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer)
{
	this->Devicecontext->PSSetConstantBuffers(0, 1, &constant_buffer->Buffer);
}


void DeviceContext::setViewportSize(UINT width, UINT height, int viewportnum)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (FLOAT)width / 2.0f;
	viewport.Height = (FLOAT)height / 2.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	D3D11_VIEWPORT viewport2 = {};
	viewport2.Width = (FLOAT)width / 2.0f;
	viewport2.Height = (FLOAT)height / 2.0f;
	viewport2.MinDepth = 0.0f;
	viewport2.MaxDepth = 1.0f;
	viewport2.TopLeftX = (FLOAT)width / 2.0f;
	viewport2.TopLeftY = (FLOAT)width / 2.0f;

	if(viewportnum == 1)
	{
		this->Devicecontext->RSSetViewports(1, &viewport);
	}
	
	else if(viewportnum == 2)
	{
		this->Devicecontext->RSSetViewports(1, &viewport2);
	}
	
	
}



void DeviceContext::drawTriangleList(UINT vertex_count, UINT startVertexIndex)
{
	this->Devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->Devicecontext->Draw(vertex_count, startVertexIndex);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT startVertexIndex)
{
	this->Devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->Devicecontext->Draw(vertex_count, startVertexIndex);
}

DeviceContext::~DeviceContext()
{
}

