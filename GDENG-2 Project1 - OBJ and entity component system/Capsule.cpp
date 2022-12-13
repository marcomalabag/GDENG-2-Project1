#include "Capsule.h"
#include "Vector2D.h"
#include "AGameObject.h"
#include "PhysicsComponent.h"

Capsule::Capsule(String name): AGameObject(name, PrimitiveType::CAPSULE)
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);

	float Resolution = 5.5f;
	this->length = 1.5f;
	this->radius = 1.5f;

	Vector3D start = Vector3D(0.0f, 0.f, 0.0f);
	Vector3D end = Vector3D(1.0f, 1.0f, 1.0f);

	Vector3D step = (end - start) / Resolution;

	for (float i = 0.0f; i < Resolution; i++)
	{
		for (float j = 0.0f; j < Resolution; j++)
		{
			float u = i * step.x + start.x;
			float v = j * step.y + start.y;
			float un = 0.0f;
			float vn = 0.0f;

			if (i + 1.0f == Resolution)
			{
				un = end.x;
			}
			else
			{
				un = (i + 1.0f) * step.x + start.x;
			}

			if (j + 1.0f == Resolution)
			{
				vn = end.y;
			}
			else
			{
				vn = (j + 1.0f) * step.y + start.y;
			}

			int verticesStartIndex = this->Vertices.size();
			vertex vertex0 = { this->cylinder(u, v), Vector3D((float)i / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f)};
			vertex vertex1 = { this->cylinder(u, vn), Vector3D((float)i / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex vertex2 = { this->cylinder(un, v), Vector3D((float)i + 1.0f / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex vertex3 = { this->cylinder(un, vn), Vector3D((float)i + 1.0f / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };

			this->Vertices.push_back(vertex0);
			this->Vertices.push_back(vertex1);
			this->Vertices.push_back(vertex2);
			this->Vertices.push_back(vertex3);
			this->Indices.push_back(verticesStartIndex);
			this->Indices.push_back(verticesStartIndex + 2);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 3);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 2);

			verticesStartIndex = this->Vertices.size();
			vertex0 = { this->sphereStart(u, v), Vector3D((float)i / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex1 = { this->sphereStart(u, vn), Vector3D((float)i / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex2 = { this->sphereStart(un, v), Vector3D((float)i + 1.0f / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex3 = { this->sphereStart(un, vn), Vector3D((float)i + 1.0f / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };

			this->Vertices.push_back(vertex0);
			this->Vertices.push_back(vertex1);
			this->Vertices.push_back(vertex2);
			this->Vertices.push_back(vertex3);
			this->Indices.push_back(verticesStartIndex);
			this->Indices.push_back(verticesStartIndex + 2);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 3);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 2);

			verticesStartIndex = this->Vertices.size();
			vertex0 = { this->sphereEnd(u, v), Vector3D((float)i / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex1 = { this->sphereEnd(u, vn), Vector3D((float)i / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex2 = { this->sphereEnd(un, v), Vector3D((float)i + 1.0f / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex3 = { this->sphereEnd(un, vn), Vector3D((float)i + 1.0f / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };

			this->Vertices.push_back(vertex0);
			this->Vertices.push_back(vertex1);
			this->Vertices.push_back(vertex2);
			this->Vertices.push_back(vertex3);
			this->Indices.push_back(verticesStartIndex);
			this->Indices.push_back(verticesStartIndex + 2);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 3);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 2);
		}
	}
	
	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(&(this->Vertices[0]), sizeof(vertex), this->Vertices.size(), shaderdata.shaderByteCode, shaderdata.sizeShader);

	

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	this->indexbuffer->load(&(this->Indices[0]), this->Indices.size());

	constant cc;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));

	this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.BASE_VERTEX_SHADER_NAME);
	this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.BASE_PIXEL_SHADER_NAME);
}

void Capsule::draw(int width, int height)
{
	constant cc;
	if (this->overrideMatrix)
	{
		cc.world = this->getLocalMatrix();
	}
	else
	{
		this->ComputeLocalMatrix();
		cc.world = this->getLocalMatrix();
	}

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.view = cameraMatrix;

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

void Capsule::update(float deltaTime)
{
}

void Capsule::saveEditState() {
	PhysicsComponent* componentAttached = (PhysicsComponent*)this->findComponentbyType(AComponent::Physics, "Physics Component");
	if (componentAttached != nullptr)
	{
		AGameObject::saveEditState();
	}
}

void Capsule::restoreEditState()
{
	PhysicsComponent* componentAttached = (PhysicsComponent*)this->findComponentbyType(AComponent::Physics, "Physics Component");
	if (componentAttached != nullptr)
	{
		AGameObject::restoreEditState();
		this->detachComponent(componentAttached);
		componentAttached = new PhysicsComponent("Physics Component", this);
		this->attachComponent(componentAttached);
	}

}

Vector3D Capsule::cylinder(float u, float v)
{
	float pi = 3.1415926f;
	Vector3D x = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D z = Vector3D(0.0f, 0.0f, 1.0f);
	Vector3D capsuleEnd = Vector3D(0.0f, 0.0f, 0.0f);


	return capsuleEnd
		+ z * cosf(2.0f * pi * u) * this->radius
		+ x * sinf(2.0f * pi * u) * this->radius
		+ y * v * this->length;
}

Vector3D Capsule::sphereStart(float u, float v)
{
	float pi = 3.1415926f;
	Vector3D x = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D z = Vector3D(0.0f, 0.0f, 1.0f);
	Vector3D capsuleTop = Vector3D(0.0f, this->length, 0.0f);

	return capsuleTop
		+ z * cosf(2.0f * pi * u) * cosf((pi / 2.0f) * v) * this->radius
		+ x * sinf(2.0f * pi * u) * cosf((pi / 2.0f) * v) * this->radius
		+ y * sinf((pi / 2.0f) * v) * this->radius;
}

Vector3D Capsule::sphereEnd(float u, float v)
{
	float pi = 3.1415926f;
	Vector3D x = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D z = Vector3D(0.0f, 0.0f, 1.0f);
	Vector3D capsuleEnd = Vector3D(0.0f, 0.0f, 0.0f);

	return capsuleEnd
		+ z * cosf(2.0f * pi * u) * cosf((pi / 2.0f) * (v - 1)) * this->radius
		+ x * sinf(2.0f * pi * u) * cosf((pi / 2.0f) * (v - 1)) * this->radius
		+ y * sinf((pi / 2.0f) * (v - 1)) * this->radius;
}

Capsule::~Capsule()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
	AGameObject::~AGameObject();
}
