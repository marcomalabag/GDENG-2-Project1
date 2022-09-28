#include "Triangle.h"


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


Triangle::Triangle()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	vertex list[] = {
		{Vector3D(-0.5f,-0.5f,0.0f), Vector3D( - 0.5f,-0.5f,0.0f), Vector3D(1,1,0), Vector3D(1,1,0)},
		{Vector3D(0.0f,0.5f,0.0f), Vector3D(0.0f,0.5f,0.0f), Vector3D(1,1,0), Vector3D(1,1,0)},
		{ Vector3D(0.5f,-0.5f,0.0f),  Vector3D(.5f,-0.5f,0.0f), Vector3D(1,1,0), Vector3D(1,1,0)}
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

void Triangle::draw()
{
	unsigned long newtime = 0;
	if (this->oldTime)
	{
		newtime = GetTickCount() - this->oldTime;
	}

	this->deltaTime = newtime / 1000.0f;
	this->oldTime = ::GetTickCount();

	this->angle += 1.57f * this->deltaTime;
	constant cc;
	cc.m_angle = this->angle;

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

	//Triangle render
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(this->vertexbuffer->getSizeVertexList(), 0);

}

void Triangle::setWindowSizeLength(float windowsizelength)
{
	this->windowSizeLength = windowsizelength;
}

void Triangle::setWindowSizeHeight(float windowsizeheight)
{
	this->windowSizeHeight = windowsizeheight;
}

void Triangle::setPosition(Vector3D Position)
{
	this->position = Position;
}

Triangle::~Triangle()
{
	this->vertexbuffer->release();
	this->vertexshader->release();
	this->pixelshader->release();
}
