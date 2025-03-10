#pragma once

#include "Vec2.h"
#include <vector>

class PhysicsObject;

struct CollisionInfo
{
	PhysicsObject* objA;
	PhysicsObject* objB;
	Vec2 _closestPoint;
	float _overlapAmount;
	bool _overlapping;
	Vec2 _overlapNormal;
	Vec2 contactPoint;

	std::vector<Vec2> polygonVertices;

	void Resolve();
};