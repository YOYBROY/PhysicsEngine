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
	Vec2 point2;

	void TryCut(Vec2 mousePos, std::vector<PhysicsObject*> bodies);
	void Draw(LineRenderer* lines, Vec2 cursorPos);
};