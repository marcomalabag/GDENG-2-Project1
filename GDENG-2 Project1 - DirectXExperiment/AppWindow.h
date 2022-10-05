#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Vector3D.h"
#include <vector>
#include "Viewport.h"


class AppWindow : public Window
{
public:

	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	void initializeEngine();

public:
	static void initialize();
	static AppWindow* getInstance();
	

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&){};
	AppWindow&operator=(AppWindow const&){};

private:
	static AppWindow* sharedInstance;


private:
	SwapChain* m_swap_chain;
	VertexBuffer* vertexbuffer;
	VertexShader* vertexshader;
	PixelShader* pixelshader;
	ConstantBuffer* constantbuffer;

	unsigned long oldTime = 0;
	float deltaTime = 0;
	float angle = 0;

	std::vector <class Triangle*> triangle;
	std::vector<class Rectangle*> rectangle;

	Vector3D positions[3];
	Vector3D TrianglePositions[3];
};

