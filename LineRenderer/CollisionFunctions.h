#pragma once

#include "CollisionInfo.h"
#include "PhysicsObject.h"
#include <functional>

inline std::function<CollisionInfo(PhysicsObject*, PhysicsObject*)> collisionThings[(int)ObjectType::COUNT][(int)ObjectType::COUNT];

void PopulateCollisionFunctionArray();

CollisionInfo CheckCollision(PhysicsObject* objA, PhysicsObject* objB);

CollisionInfo CircleToCircle(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo CircleToBox(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo CircleToPlane(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo BoxToCircle(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo BoxToBox(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo BoxToPlane(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo PlaneToCircle(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo PlaneToBox(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo PlaneToPlane(PhysicsObject* objA, PhysicsObject* objB);
