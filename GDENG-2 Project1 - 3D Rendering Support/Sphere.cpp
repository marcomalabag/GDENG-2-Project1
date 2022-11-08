#include "Sphere.h"

Sphere::Sphere(string name):AGameObject(name)
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);

	float radius = 1.5f;
	int stackCount = 12;
	int sectorCount = 12;

	float x, y, z, xy;
	float pi = 3.1415926;
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



	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(&(this->vertices[0]), sizeof(vertex), this->vertices.size(), shaderdata.shaderByteCode, shaderdata.sizeShader);

	

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

	this->indexbuffer->load(&(this->indices[0]), this->indices.size());
	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));

	this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.BASE_VERTEX_SHADER_NAME);
	this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.BASE_PIXEL_SHADER_NAME);
}

void Sphere::draw(int width, int height)
{
	constant cc;
	Matrix4x4 temp;

	this->Summation.setIdentity();
	this->translate.setIdentity();
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



