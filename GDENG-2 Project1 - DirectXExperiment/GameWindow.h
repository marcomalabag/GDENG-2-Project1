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

class GameWindow: public Window
{
public:
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	void CreateGameWindow();

public:
	static void initialize();
	static GameWindow* getInstance();

private:
	GameWindow();
	~GameWindow();
	GameWindow(GameWindow const&) {};
	GameWindow& operator=(GameWindow const&) {};

private:
	static GameWindow* sharedInstance;


private:
	SwapChain* m_swap_chain_game;
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

