#include "PhysicsComponent.h"
#include "BaseSystem.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
	BaseSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	Vector3D scale = this->getOwner()->getLocalScale();
	Transform transform;
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2, scale.y / 2, scale.z / 2));

}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float Matrix[16];
	transform.getOpenGLMatrix(Matrix);

	this->getOwner()->setLocalMatrix(Matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}

PhysicsComponent::~PhysicsComponent()
{
}