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

	std::vector<float> projectionDepths;
	std::vector<Vec2> cuttingEdges;
	std::vector<Vec2> cutPoints;

	void TryCut(Vec2 cursorPos, std::vector<PhysicsObject*>& bodies);
	void Draw(LineRenderer* lines, Vec2 cursorPos);
	Vec2 RemapFromFloatToVec2(float value, float aMin, float aMax, Vec2 bMin, Vec2 bMax);
};