#include "DeviceContext.h"
#include "SwapChain.h"	

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context)
{
	this->Devicecontext = device_context;
}

ID3D11DeviceContext* DeviceContext::getContext()
{
	return this->Devicecontext;
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
	ID3D11RenderTargetView* renderview = swapchain->getRenderTargetView();
	ID3D11DepthStencilView* depthview = swapchain->getDepthStencilView();
	this->Devicecontext->ClearRenderTargetView(renderview, clear_color);
	this->Devicecontext->ClearDepthStencilView(depthview, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	this->Devicecontext->OMSetRenderTargets(1, &renderview, depthview);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->getSizeVertexBuffer();
	UINT offset = 0;

	this->Devicecontext->IASetVertexBuffers(0, 1, &vertex_buffer->Buffer, &stride, &offset);
	this->Devicecontext->IASetInputLayout(vertex_buffer->Layout);
}

void DeviceContext::setVertexBufferTextured(VertexBufferTextured* textured_vertex_buffer)
{
	UINT stride = textured_vertex_buffer->getSizeVertexBuffer();
	UINT offset = 0;

	this->Devicecontext->IASetVertexBuffers(0, 1, &textured_vertex_buffer->Buffer, &stride, &offset);
	this->Devicecontext->IASetInputLayout(textured_vertex_buffer->Layout);
}

void DeviceContext::setIndexBuffer(IndexBuffer* index_buffer)
{
	this->Devicecontext->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::setVertexShader(VertexShader* vertex_shader)
{
	this->Devicecontext->VSSetShader(vertex_shader->vertexShader, nullptr, 0);
}

void DeviceContext::setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer)
{
	this->Devicecontext->VSSetConstantBuffers(0, 1, &constant_buffer->Buffer);
}

void DeviceContext::setTexture(VertexShader* vertex_shader, Texture* texture)
{
	this->Devicecontext->VSSetShaderResources(0, 1, &texture->shaderResView);
}

void DeviceContext::setPixelShader(PixelShader* pixel_shader)
{
	this->Devicecontext->PSSetShader(pixel_shader->pixelshader, nullptr, 0);
}

void DeviceContext::setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer)
{
	this->Devicecontext->PSSetConstantBuffers(0, 1, &constant_buffer->Buffer);
}

void DeviceContext::setTexture(PixelShader* pixel_shader, Texture* texture)
{
	this->Devicecontext->PSSetShaderResources(0, 1, &texture->shaderResView);
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

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	this->Devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->Devicecontext->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT startVertexIndex)
{
	this->Devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->Devicecontext->Draw(vertex_count, startVertexIndex);
}

DeviceContext::~DeviceContext()
{
}

