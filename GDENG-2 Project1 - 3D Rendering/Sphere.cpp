#include "Sphere.h"

Sphere::Sphere(string name, void* shaderByteCode, size_t sizeShader):AGameObject(name)
{
	float radius = 1.5f;
	int stackCount = 12;
	int sectorCount = 12;

	float x, y, z, xy;
	float pi = atan(1) * 4.0f;
	float sectorStep = 2 * pi / (float)sectorCount;
	float stackStep = pi / (float)stackCount;
	float sectorAngle, stackAngle;

	for(int i = 0; i <= stackCount; i++)
	{
		stackAngle = pi / 2.0f - i * stackStep;
		xy = radius * cosf(stackAngle);
		y = radius * sinf(stackAngle);

		for(int j = 0; j <= sectorCount; j++)
		{
			sectorAngle = j * sectorStep;
			z = xy * cosf(sectorAngle);
			x = xy * sinf(sectorAngle);
			
			vertex vertexsector = { Vector3D(x, y, z), Vector3D(1,0,0),  Vector3D(0.2f,0,0) };
			this->vertices.push_back(vertexsector);
		}
	}


	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(&(this->vertices[0]), sizeof(vertex), this->vertices.size(), shaderByteCode, sizeShader);

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

	int k1, k2;

	for(int i = 0; i < stackCount; i++)
	{
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;

		for(int j = 0; j < sectorCount; j++)
		{
			if (i != 0)
			{
				this->indices.push_back(k1);
				this->indices.push_back(k1 + 1);
				this->indices.push_back(k2);
			}

			if (i != (stackCount - 1))
			{
				this->indices.push_back(k1 + 1);
				this->indices.push_back(k2 + 1);
				this->indices.push_back(k2);
			}

			k1++;
			k2++;
		}
	}

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->indexbuffer->load(&(this->indices[0]), this->indices.size());
	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));
}

void Sphere::draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader)
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
		6.0f
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

	this->deltaTime = (oldDelta) ? ((newDelta - oldDelta) / 100.0f) : 0;
}

void Sphere::update(float deltaTime)
{
	this->deltaTime = deltaTime;
}

Sphere::~Sphere()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
	AGameObject::~AGameObject();
}




