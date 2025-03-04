#pragma once

#include <vector>

#include "PhysicsObject.h"
#include "Polygon.h"

enum class BoxType 
{
	U = 3,
	R = 7,
	D = 11,
	L = 13,
	UR = 10,
	UD = 14,
	UL = 16,
	RD = 18,
	RL = 20,
	DL = 24,
	URD = 21,
	RDL = 31,
	DLU = 27,
	LUR = 23,
	URDL = 34
};

class Box : public Polygon
{
protected:
	float _width;
	float _height;
	bool _visible = false;
	BoxType _boxType = BoxType::URDL;
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

	void SetBoxType(int boxType) { _boxType = (BoxType) boxType; }
};