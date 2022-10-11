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
#include "EngineTime.h"
#include "IndexBuffer.h"


class AppWindow : public Window
{
public:

	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	void initializeEngine();
	void updateQuadPosition();

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
	IndexBuffer* indexbuffer;

	long oldTime;
	long newdeltaTime;
	float deltaTime = 0;

	float angle = 0;
	float ticks = 0.0f;

	float deltaPosition;
	float deltaScale;
	float deltaRotaion;

	std::vector <class Triangle*> triangle;
	std::vector<class Rectangle*> rectangle;

	Vector3D positions[3];
	Vector3D TrianglePositions[3];
};

