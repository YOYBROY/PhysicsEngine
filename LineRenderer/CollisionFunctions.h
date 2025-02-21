#pragma once

#include "CollisionInfo.h"
#include "PhysicsObject.h"
#include <functional>

inline std::function<CollisionInfo(PhysicsObject*, PhysicsObject*)> collisionThings[(int)ObjectType::COUNT][(int)ObjectType::COUNT];

void PopulateCollisionFunctionArray();

CollisionInfo CheckCollision(PhysicsObject* objA, PhysicsObject* objB);

CollisionInfo CircleToCircle(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo CircleToPlane(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo CircleToPolygon(PhysicsObject* objA, PhysicsObject* objB);

CollisionInfo PlaneToCircle(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo PlaneToPlane(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo PlaneToPolygon(PhysicsObject* objA, PhysicsObject* objB);

CollisionInfo PolygonToCircle(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo PolygonToPlane(PhysicsObject* objA, PhysicsObject* objB);
CollisionInfo PolygonToPolygon(PhysicsObject* objA, PhysicsObject* objB);