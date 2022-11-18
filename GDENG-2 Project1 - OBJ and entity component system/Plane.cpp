#include "Plane.h"

Plane::Plane(String name): Cube(name)
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.01f,-0.5f),    Vector3D(1,1,1)},
		{Vector3D(-0.5f,0.01f,-0.5f),    Vector3D(1,1,1)},
		{ Vector3D(0.5f,0.01f,-0.5f),   Vector3D(1,1,1)},
		{ Vector3D(0.5f,-0.01f,-0.5f),     Vector3D(1,1,1)},
		//BACK FACE
		{ Vector3D(0.5f,-0.01f,0.5f),    Vector3D(1,1,1)},
		{ Vector3D(0.5f,0.01f,0.5f),    Vector3D(1,1,1)},
		{ Vector3D(-0.5f,0.01f,0.5f),   Vector3D(1,1,1)},
		{ Vector3D(-0.5f,-0.01f,0.5f),     Vector3D(1,1,1)}
	};

	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderdata.shaderByteCode, shaderdata.sizeShader);
	
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->indexbuffer->load(index_list, size_index_list);
	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));

	this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.BASE_VERTEX_SHADER_NAME);
	this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.BASE_PIXEL_SHADER_NAME);
}

void Plane::draw(int width, int height)
{
	constant cc;
	this->ComputeLocalMatrix();
	cc.world = this->getLocalMatrix();

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.view = cameraMatrix;

	/*
	cc.projection.setOrthoLH
	(
		width / 300.0f,
		height / 300.0f,
		-4.0f,
		4.0f
	);
	*/
	float aspectRatio = (float)width / (float)height;

	cc.projection.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	DeviceContext* device = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	this->constantbuffer->update(device, &cc);


	device->setConstantBuffer(this->vertex_shader, this->constantbuffer);
	device->setConstantBuffer(this->pixel_shader, this->constantbuffer);

	device->setVertexShader(this->vertex_shader);
	device->setPixelShader(this->pixel_shader);

	device->setVertexBuffer(this->verterbuffer);
	device->setIndexBuffer(this->indexbuffer);
	device->drawIndexedTriangleList(this->indexbuffer->getSizeIndexList(), 0, 0);
	
}

Plane::~Plane()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
}



