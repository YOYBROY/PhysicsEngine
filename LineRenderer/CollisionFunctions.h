#pragma once

#include "CollisionInfo.h"

class PhysicsObject;

CollisionInfo CircleToCircle(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo CircleToBox(PhysicsObject* objA, PhysicsObject* objB);