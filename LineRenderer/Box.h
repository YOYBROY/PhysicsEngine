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

	ObjectType _objectType = BOX;

public:
	Box(Vec2 position, float width, float height, float mass, float elasticity);
	Box(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity);

	void Update(float delta) override;
	void Draw(LineRenderer* lines) override;

	float GetWidth() { return _width; }
	void SetWidth(float width) { _width = width; }

	float GetHeight() { return _height; }
	void GetHeight(float height) { _height = height; }

	float GetMinX() { return _minX; }
	float GetMaxX() { return _maxX; }
	float GetMinY() { return _minY; }
	float GetMaxY() { return _maxY; }

	ObjectType GetObjectType() override { return _objectType; }
};