#include "Triangle.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};


Triangle::Triangle(void* shader_byte_code, size_t size_shader, VertexShader* vertexShader)
{
	vertex list[] = {
		{-0.5f,-0.5f,0.0f, -0.5f,-0.5f,0.0f, 1,1,0, 1,1,0},
		{0.0f,0.5f,0.0f, 0.0f,0.5f,0.0f, 1,1,0, 1,1,0},
		{ 0.5f,-0.5f,0.0f,  0.5f,-0.5f,0.0f, 1,1,0, 1,1,0}
	};

	this->vertexbuffer = GraphicsEngine::getInstance()->createVertexBuffer();

	UINT size_list = ARRAYSIZE(list);

	this->vertexshader = vertexShader;
	this->vertexbuffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->pixelshader = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();
	

	constant cc;
	cc.m_angle = 0;

	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
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

	this->constantbuffer->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(this->vertexshader, this->constantbuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(this->pixelshader, this->constantbuffer);


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(this->vertexshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(this->pixelshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(this->vertexbuffer);

	//Triangle render
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(this->vertexbuffer->getSizeVertexList(), 0);

}

Triangle::~Triangle()
{
	this->vertexbuffer->release();
	this->vertexshader->release();
	this->pixelshader->release();
}
