#include "Viewport.h"

Viewport* Viewport::sharedInstance = NULL;

Viewport::Viewport()
{
	
}


D3D11_VIEWPORT Viewport::getViewport(int num)
{
    return this->viewports.at(num);
}

void Viewport::add(UINT width, UINT height, float MinDepth, float MaxDepth, float TopLeftX, float TopLeftY)
{
    D3D11_VIEWPORT port = {};
    port.Width = width;
    port.Height = height;
    port.MinDepth = MinDepth;
    port.MaxDepth = MaxDepth;
    port.TopLeftX = TopLeftX;
    port.TopLeftY = TopLeftY;

    this->viewports.push_back(port);

    
}

void Viewport::initialize()
{
    sharedInstance = new Viewport();
}

Viewport* Viewport::getInstance()
{
    if(sharedInstance != NULL)
    {
        return sharedInstance;
    }
    
}

Viewport::~Viewport()
{
}
