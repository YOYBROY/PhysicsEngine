#pragma once
#include "PhysicsObject.h"

class Circle : public PhysicsObject
{
private:
	float _radius;
	ObjectType _objectType = CIRCLE;

public:
	Circle(Vec2 position, float radius, float mass, float elasticity);
	Circle(Vec2 position, float radius, float mass, float elasticity, Vec2 velocity);
	void Draw(LineRenderer* lines) override;

	float GetRadius() { return _radius; }
	void SetRadius(float radius) { _radius = radius; }

	ObjectType GetObjectType() override { return _objectType; }
};