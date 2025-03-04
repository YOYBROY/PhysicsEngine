#pragma once

#include <vector>

#include "PhysicsObject.h"
#include "Polygon.h"

#define SKIN_THICKNESS 0.001f
#define JUMP_HEIGHT 7.0f
#define MOVE_SPEED 5.0f

class Player : public Polygon
{
protected:
	float _width;
	float _height;

	float maxStepHeight = 0.0f;
	float maxStepFraction = 0.15f;

	float edgeSlip = 0.0f;
	float edgeSlipFraction = 0.05f;
public:
	bool grounded = true;

	Player(Vec2 position, float width, float height, float mass, float elasticity);
	Player(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity);
	Player(Vec2 position, float width, float height, float mass, float elasticity, float orientation);
	Player(Vec2 position, float width, float height, float mass, float elasticity, float orientation, Vec2 velocity);

	void Update(float delta) override;
	void Draw(LineRenderer* lines) override;

	float GetWidth() { return _width; }
	void SetWidth(float width) { _width = width; }

	float GetHeight() { return _height; }
	void SetHeight(float height) { _height = height; }

	ObjectType GetObjectType() override { return ObjectType::PLAYER; }

	void HandleInput();
	void AttemptJump();
};