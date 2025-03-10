#pragma once

#include "Vec2.h"
#include "LineRenderer.h"

enum ObjectType
{
	CIRCLE,
	BOX,
	PLANE,
	POLYGON,
	PLAYER,

	COUNT
};

class PhysicsObject
{
protected:
	float _mass = 0;
	Vec2 _position;
	Vec2 _velocity;
	Vec2 _acceleration;
	float _elasticity;
	Colour _colour;
	Vec2 _forceAccumulator;
	Vec2 _gravity = Vec2(0,0);

	float _orientation;
	float _angularVelocity;
	float _moment;

public:
	PhysicsObject();
	virtual ~PhysicsObject() = default;
	PhysicsObject(Vec2 position, float mass, float elasticity);
	PhysicsObject(Vec2 position, float mass, float elasticity, Vec2 velocity);
	virtual void Update(float delta);
	virtual void Draw(LineRenderer* lines) = 0;

	float GetMass() { return _mass; }
	void SetMass(float mass) { _mass = mass; }

	float GetInverseMass();

	Vec2& GetPosition() { return _position; }
	void SetPosition(Vec2 position) { _position = position; }

	Vec2& GetVelocity() { return _velocity; }
	void SetVelocity(Vec2 velocity) { _velocity = velocity; }

	float& GetAngularVelocity() { return _angularVelocity; }
	void SetAngularVelocity(float angularVelocity) { _angularVelocity -= angularVelocity; }

	Vec2& GetAcceleration() { return _acceleration; }
	void SetAcceleration(Vec2 acceleration) { _acceleration = acceleration; }

	float GetElasticity() { return _elasticity; }
	void SetElasticity(float elasticity) { _elasticity = elasticity; }

	Colour GetColour() { return _colour; }
	void SetColour(Colour colour) { _colour = colour; }

	virtual ObjectType GetObjectType() = 0;
	
	void AddForce(Vec2 force, Vec2 position);
	void AddImpulse(Vec2 impulse);
};