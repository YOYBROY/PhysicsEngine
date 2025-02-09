#include "PhysicsObject.h"
#include "LineRenderer.h"
#include "Application.h"

PhysicsObject::PhysicsObject()
{
}

PhysicsObject::PhysicsObject(Vec2 position, float mass, float elasticity) : _position(position), _mass(mass), _elasticity(elasticity)
{
}

PhysicsObject::PhysicsObject(Vec2 position, float mass, float elasticity, Vec2 Velocity) : _position(position), _mass(mass), _elasticity(elasticity), _velocity(Velocity)
{
}

void PhysicsObject::Update(float delta)
{
	//_acceleration = /*_gravity + */
	_velocity += _acceleration * delta;
	_position += _velocity * delta;
}

void PhysicsObject::Draw(LineRenderer* lines)
{
}