#include "Plane.h"

Plane::Plane(string name, void* shaderByteCode, size_t sizeShader): Cube(name, shaderByteCode,  sizeShader)
{
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,1), Vector3D(1,1,1) },
	};

	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);
	
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0  //SECOND TRIANGLE
	};

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->indexbuffer->load(index_list, size_index_list);
	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));
}

void Plane::draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader)
{
	constant cc;
	Matrix4x4 temp;

	this->Summation.setIdentity();
	this->Scale.setIdentity();

	translate.setTranslation(this->getLocalPosition());
	Scale.setScale(this->getLocalScale());
	rotation = Vector3D(this->getLocalRotation());

	this->RotationZ.setIdentity();
	this->RotationZ.setRotationZ(rotation.z);

	this->RotationF.setIdentity();
	this->RotationF.setRotationX(rotation.x);

	this->RotationGl.setIdentity();
	this->RotationGl.setRotationY(rotation.y);

	this->RotationTotal.setIdentity();
	this->RotationTotal = this->RotationTotal.mulMatrix(RotationF.mulMatrix(RotationGl.mulMatrix(RotationZ)));
	this->Summation = this->Summation.mulMatrix(Scale.mulMatrix(this->RotationTotal));
	this->Summation = this->Summation.mulMatrix(this->translate);
	cc.world = this->Summation;

	cc.view.setIdentity();

	cc.projection.setOrthoLH
	(
		(width) / 300.0f,
		(height) / 300.0f,
		-4.0f,
		4.0f
	);

	this->constantbuffer->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(vertexshader, this->constantbuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(pixelshader, this->constantbuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertexshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixelshader);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(this->verterbuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(this->indexbuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(this->indexbuffer->getSizeIndexList(), 0, 0);
	this->oldDelta = this->newDelta;
	this->newDelta += this->ticks;

	this->deltaTime = (oldDelta) ? ((newDelta - oldDelta) / 1000.0f) : 0;
}

Plane::~Plane()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
}




