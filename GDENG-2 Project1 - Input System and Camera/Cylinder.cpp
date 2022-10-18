#include "Cylinder.h"

Cylinder::Cylinder(string name, void* ShaderByteCode, size_t SizeShader): AGameObject(name)
{
	float radius = 1.5f;
	int sectorCount = 12;
	float height = 1.5f;
	

	float pi = 3.1415926f;
	float sectorStep = 2 * pi / (float)sectorCount;
	float sectorAngle;

	for(int i = 0; i <= sectorCount; i++)
	{
		sectorAngle = i * sectorStep;
		Vector3D vector = Vector3D(sinf(sectorAngle), 0.0f, cosf(sectorAngle));
		this->CircleVertices.push_back(vector);
	}

	for(int i = 0; i < 2; i++)
	{
		float h = -height / 2.0f + i * height;
		int k = 0;
		for(int j = 0; j <= sectorCount; j++)
		{
			Vector3D UnitVertex = this->CircleVertices[k];

			vertex Vertex = { Vector3D(UnitVertex.x * radius, h, UnitVertex.z * radius), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };
			this->Vertices.push_back(Vertex);
			k++;
		}
	}

	this->BaseCenterIndex = this->Vertices.size();
	this->TopCenterIndex = this->BaseCenterIndex + sectorCount + 1;

	for(int i = 0; i < 2; i++)
	{
		float h = -height / 2.0f + i * height;
		vertex Vertex = { Vector3D(0.0f, h, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };
		this->Vertices.push_back(Vertex);
		int k = 0;

		for(int j = 0; j < sectorCount; j++)
		{
			Vector3D unitVertex = this->CircleVertices[k];

			vertex Vertex = { Vector3D(unitVertex.x * radius, h, unitVertex.z * radius),
			Vector3D(1, 1, 1), Vector3D(1, 1, 1) };

			this->Vertices.push_back(Vertex);
			k++;
		}
	}

	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(&(this->Vertices[0]), sizeof(vertex), this->Vertices.size(), ShaderByteCode, SizeShader);

	int k1 = 0;
	int k2 = sectorCount + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		this->Indices.push_back(k1);
		this->Indices.push_back(k1 + 1);
		this->Indices.push_back(k2);

		this->Indices.push_back(k2);
		this->Indices.push_back(k1 + 1);
		this->Indices.push_back(k2 + 1);

		k1++;
		k2++;
	}

	int k = this->BaseCenterIndex + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		if (i < sectorCount - 1)
		{
			this->Indices.push_back(this->BaseCenterIndex);
			this->Indices.push_back(k + 1);
			this->Indices.push_back(k);
		}
		else
		{
			this->Indices.push_back(this->BaseCenterIndex);
			this->Indices.push_back(this->BaseCenterIndex + 1);
			this->Indices.push_back(k);
		}
		k++;
	}

	k = this->TopCenterIndex + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		if (i < sectorCount - 1)
		{
			this->Indices.push_back(this->TopCenterIndex);
			this->Indices.push_back(k);
			this->Indices.push_back(k + 1);
		}
		else
		{
			this->Indices.push_back(this->TopCenterIndex);
			this->Indices.push_back(k);
			this->Indices.push_back(this->TopCenterIndex + 1);
		}
		k++;
	}

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	this->indexbuffer->load(&(this->Indices[0]), this->Indices.size());

	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));
}

void Cylinder::draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader)
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

void Cylinder::update(float deltaTime)
{
	this->deltaTime = deltaTime;
}

Cylinder::~Cylinder()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
	AGameObject::~AGameObject();
}
