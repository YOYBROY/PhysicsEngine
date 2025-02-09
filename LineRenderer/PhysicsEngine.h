#pragma once

#include "Application.h"

#include <vector>

class PhysicsObject;

class PhysicsEngine : public Application
{
public:
	PhysicsEngine();
	std::vector<PhysicsObject*> _physicsObjects;
	
	Vec2 _gravity;

	void Initialise() override;
	void Update(float delta) override;
};