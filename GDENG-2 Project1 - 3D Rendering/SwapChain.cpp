#include "SwapChain.h"
#include "GraphicsEngine.h"
#include <iostream>

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
    ID3D11Device* device = GraphicsEngine::getInstance()->getD3Ddevice();

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 1;
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;


    HRESULT hr = GraphicsEngine::getInstance()->getFactory()->CreateSwapChain(device, &desc, &m_swap_chain);

    if(FAILED(hr))
    {
        std::cout << "Failed to create swap chain";
        return false;
    }

    ID3D11Texture2D* buffer = NULL;
    hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

    if(FAILED(hr))
    {
        std::cout << "Failed to get buffer";
        return false;
    }

    hr = device->CreateRenderTargetView(buffer, NULL, &this->RenderTargetView);
    buffer->Release();

    if (FAILED(hr))
    {
        std::cout << "Failed to create render target view";
        return false;
    }

    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = width;
    texDesc.Height = height;
    texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    texDesc.MipLevels = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.MiscFlags = 0;
    texDesc.ArraySize = 1;
    texDesc.CPUAccessFlags = 0;

    hr = device->CreateTexture2D(&texDesc, NULL, &buffer);
    if(FAILED(hr))
    {
        std::cout << "Failed to create depth result" << "\n";
    }

    hr = device->CreateDepthStencilView(buffer, NULL, &this->DepthView);
    if (FAILED(hr))
    {
        std::cout << "Failed to create depth stencil view" << "\n";
    }

    buffer->Release();

	return true;
}

bool SwapChain::present(bool vsync)
{
    this->m_swap_chain->Present(vsync, NULL);

    return true;
}

ID3D11RenderTargetView* SwapChain::getRenderTargetView()
{
    return this->RenderTargetView;
}

ID3D11DepthStencilView* SwapChain::getDepthStencilView()
{
    return this->DepthView;
}

bool SwapChain::release()
{
    m_swap_chain->Release();
    delete this;
    return true;
}

SwapChain::~SwapChain()
{
}