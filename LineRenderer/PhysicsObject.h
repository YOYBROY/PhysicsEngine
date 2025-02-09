#pragma once

#include "Vec2.h"
#include "LineRenderer.h"

enum ObjectType
{
	CIRCLE,
	BOX,
	PLANE,

	COUNT
};

class PhysicsObject

{
protected:
	float _mass;
	Vec2 _position;
	Vec2 _velocity;
	Vec2 _acceleration;
	float _elasticity;
	Colour _colour;
	int _collisionAccumulation;

public:
	PhysicsObject();
	PhysicsObject(Vec2 position, float mass, float elasticity);
	PhysicsObject(Vec2 position, float mass, float elasticity, Vec2 velocity);
	virtual void Update(float delta);
	virtual void Draw(LineRenderer* lines) = 0;

	float GetMass() { return _mass; }
	void SetMass(float mass) { _mass = mass; }

	Vec2 GetPosition() { return _position; }
	void SetPosition(Vec2 position) { _position = position; }

	Vec2 GetVelocity() { return _velocity; }
	void SetVelocity(Vec2 velocity) { _velocity = velocity; }

	Vec2 GetAcceleration() { return _acceleration; }
	void SetAcceleration(Vec2 acceleration) { _acceleration = acceleration; }

	float GetElasticity() { return _elasticity; }
	void SetElasticity(float elasticity) { _elasticity = elasticity; }

	Colour GetColour() { return _colour; }
	void SetColour(Colour colour) { _colour = colour; }

	virtual ObjectType GetObjectType() = 0;
	
	void AddCollisionAccumulation(int acummulation) { _collisionAccumulation += acummulation; }
};