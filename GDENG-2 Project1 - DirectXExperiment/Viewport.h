#pragma once
#include"DeviceContext.h"
#include <vector>

class Viewport
{

public:
	D3D11_VIEWPORT getViewport(int num);
	void add(UINT width, UINT height, float MinDepth, float MaxDepth, float TopLeftX, float TopLeftY);

public:
	static void initialize();
	static Viewport* getInstance();

private:
	static Viewport* sharedInstance;

private:
	Viewport();
	~Viewport();
	Viewport(Viewport const&) {};
	Viewport& operator=(Viewport const&) {};


	std::vector <D3D11_VIEWPORT> viewports;
};

