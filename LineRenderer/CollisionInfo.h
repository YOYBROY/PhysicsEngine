#pragma once

#include "Vec2.h"

class PhysicsObject;

struct CollisionInfo
{
	PhysicsObject* objA;
	PhysicsObject* objB;
	Vec2 _closestPoint;
	float _overlapAmount;
	bool _overlapping;
	Vec2 _overlapNormal;

	void Resolve();
};