#include "Rectangle.h"
#include "Vector3D.h"



struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 projection;
	float m_angle;
};


Rectangle::Rectangle()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	//slide 13 vertex list
	/*
	vertex list[] =
	{
		//X - Y - Z
		{Vector3D(-0.8f,-0.9f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.91f,0.3f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),    Vector3D(1,1,0), Vector3D(0,1,1)}, // POS2
		{Vector3D(0.25f,-0.2f,0.0f),     Vector3D(0.75f,-0.73f,0.0f),   Vector3D(0,0,1),  Vector3D(1,0,0)},// POS2
		{Vector3D(0.18f,0.1f,0.0f),      Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1)}
	};
	*/
	//slide 14 vertex list
	
	vertex list[] =
	{
		//X - Y - Z
		{Vector3D(-0.65f,-0.83f,0.0f),    Vector3D(-0.21f,-0.1f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.82f,0.2f,0.0f),     Vector3D(-0.11f,0.81f,0.0f),    Vector3D(1,1,0), Vector3D(0,1,1)}, // POS2
		{Vector3D(0.93f,-0.2f,0.0f),     Vector3D(0.11f,-0.73f,0.0f),   Vector3D(0,0,1),  Vector3D(1,0,0)},// POS2
		{Vector3D(0.61f,-0.83f,0.0f),      Vector3D(0.88f,0.88f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1)}
	};
	

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	this->vertexshader = graphEngine->createVertexShader(shader_byte_code, size_shader);

	this->vertexbuffer = graphEngine->createVertexBuffer();

	UINT size_list = ARRAYSIZE(list);

	this->vertexbuffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->pixelshader = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();


	constant cc;
	cc.m_angle = 0;

	this->constantbuffer = graphEngine->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));

}

void Rectangle::draw()
{
	
	//std::cout << "Tick count" << this->ticks << "\n";

	/*
	unsigned long newtime = 0;
	if (this->oldTime )
	{
		newtime = GetTickCount() - this->oldTime;
	}

	this->deltaTime = newtime / 1000.0f;
	this->oldTime = ::GetTickCount();

	this->angle += 1.57f * this->deltaTime;
	*/

	

	if (this->speed < this->cooldownrate && state)
	{
		this->speed += EngineTime::getDeltaTime();
		
		this->ticks += (EngineTime::getDeltaTime() * 1.0f);
	}
	else
	{
		state = false;
		
		this->speed -= EngineTime::getDeltaTime();
		this->ticks -= (EngineTime::getDeltaTime() * 1.0f);
		if(this->speed < -0.1f)
		{
			state = true;
			this->ticks = 0;
			this->speed = 0;
		}
	}
	


	std::cout << "Animation Speed: " << this->speed << "\n";
	constant cc;
	cc.m_angle = this->speed * this->ticks;
	

	Matrix4x4 temp;
	
	
	temp.setTranslation(position);
	cc.world.setScale(Vector3D(.5, .25, 0.0));
	cc.world *= temp;

	cc.view.setIdentity();
	cc.projection.setOrthoLH(
		windowSizeLength,
		windowSizeHeight,
		-4.0f,
		4.0f);




	this->constantbuffer->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(this->vertexshader, this->constantbuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(this->pixelshader, this->constantbuffer);


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(this->vertexshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(this->pixelshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(this->vertexbuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(this->vertexbuffer->getSizeVertexList(), 0);

}

void Rectangle::setWindowSizeLength(float windowsizelength)
{
	this->windowSizeLength = windowsizelength;
	
}

void Rectangle::setWindowSizeHeight(float windowsizeheight)
{
	this->windowSizeHeight = windowsizeheight;
}

void Rectangle::setPosition(Vector3D Position)
{
	this->position = Position;
}

Rectangle::~Rectangle()
{
	this->vertexbuffer->release();
	this->vertexshader->release();
	this->pixelshader->release();
}
