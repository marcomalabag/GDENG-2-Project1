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


void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	this->Devicecontext->RSSetViewports(1, &viewport);
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

