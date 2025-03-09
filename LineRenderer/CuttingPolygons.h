#pragma once

#include <vector>

#include "Vec2.h"
#include "LineRenderer.h"
#include "PhysicsObject.h"

class CuttingPolygons
{
private:


public:
	bool cutting;
	Vec2 point1;

	void Draw(LineRenderer* lines, Vec2 cursorPos);
	void TryCut(Vec2 cursorPos, std::vector<PhysicsObject*>& bodies);
};