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

	
public:
	bool debug = false;
	bool grounded = true;
	float maxStepHeight = 0.0f;
	float maxStepFraction = 0.25f;

	float headSlip = 0.0f;

	float footSlip = 0.0f;
	float footSlipFraction = 0.1f;

	bool umbrella = false;
	float umbrellaAngle = 0.0f;
	float umbrellaAngleSpeed = 300.0f;

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

	void HandleInput(float delta);
	void AttemptJump();
};