#pragma once

#include <vector>

#include "PhysicsObject.h"
#include "Polygon.h"

class Box : public Polygon
{
protected:
	float _width;
	float _height;
	bool _visible = true;
public:
	Box(Vec2 position, float width, float height, float mass, float elasticity);
	Box(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity);
	Box(Vec2 position, float width, float height, float mass, float elasticity, float orientation);
	Box(Vec2 position, float width, float height, float mass, float elasticity, float orientation, Vec2 velocity);

	void Update(float delta) override;
	void Draw(LineRenderer* lines) override;

	float GetWidth() { return _width; }
	void SetWidth(float width) { _width = width; }

	float GetHeight() { return _height; }
	void SetHeight(float height) { _height = height; }

	bool GetVisible() { return _visible; }
	void SetVisible(bool visible) { _visible = visible; }
};