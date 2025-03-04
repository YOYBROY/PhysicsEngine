#pragma once

#include "Application.h"
#include "Player.h"

#include <vector>

class Platformer;

class Platformer : public Application
{
private:
	std::vector<PhysicsObject*> _dynamicBodies;
	std::vector<PhysicsObject*> _staticBodies;

	Player* player = nullptr;

public:
	Platformer();
	~Platformer();

	Vec2 _gravity;

	void Initialise() override;
	void Update(float delta) override;

	void OnKeyPress(Key key) override;
};