#pragma once

#include "Vec2.h"

class PhysicsObject;

struct CollisionInfo
{
	PhysicsObject* objA;
	PhysicsObject* objB;

	float _overlapAmount;
	bool _overlapping;
	Vec2 _overlapNormal;
};