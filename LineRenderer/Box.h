#pragma once

#include "PhysicsObject.h"

class Box : public PhysicsObject
{
protected:
	float _width;
	float _height;
	float _minX;
	float _maxX;
	float _minY;
	float _maxY;

public:
	Box(Vec2 position, float width, float height, float mass, float elasticity);
	Box(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity);

	void Draw(LineRenderer* lines) override;
};