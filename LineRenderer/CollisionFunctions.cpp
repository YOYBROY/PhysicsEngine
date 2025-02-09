#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"

#include<iostream>
#include <vector>

void PopulateCollisionFunctionArray()
{
	collisionThings[CIRCLE][CIRCLE] = CircleToCircle;
	collisionThings[CIRCLE][BOX] = CircleToBox;
	collisionThings[CIRCLE][PLANE] = CircleToPlane;
	collisionThings[BOX][CIRCLE] = BoxToCircle;
	collisionThings[BOX][BOX] = BoxToBox;
	collisionThings[BOX][PLANE] = BoxToBox;
	collisionThings[PLANE][CIRCLE] = PlaneToCircle;
	collisionThings[PLANE][BOX] = PlaneToBox;
	collisionThings[PLANE][PLANE] = PlaneToPlane;
}
CollisionInfo CheckCollision(PhysicsObject* objA, PhysicsObject* objB)
{
	return collisionThings[(int)objA->GetObjectType()][(int)objB->GetObjectType()](objA, objB);
}

CollisionInfo CircleToCircle(PhysicsObject* objA, PhysicsObject* objB)
{
    CollisionInfo collInfo;
    Circle* circleA = (Circle*)objA;
    Circle* circleB = (Circle*)objB;

    Vec2 displacement = circleA->GetPosition() - circleB->GetPosition();
    float distance = displacement.GetMagnitude();

    collInfo.objA = circleA;
    collInfo.objB = circleB;
    collInfo._overlapNormal = displacement.Normalise();
    collInfo._overlapAmount = distance - (circleA->GetRadius() + circleB->GetRadius());
    collInfo._overlapping = collInfo._overlapAmount < 0;
	
	if (collInfo._overlapping)
	{
		std::cout << "Circle to Circle" << std::endl;
	}

    return collInfo;
}
CollisionInfo CircleToBox(PhysicsObject* objA, PhysicsObject* objB)
{
	//If you put the center of the circle inside the box then there is 
	//		no nearest point so the overlap normal will be 0,0 and it won't know which was to depen
	CollisionInfo collInfo;
	Circle* circleA = (Circle*)objA;
	Box* boxB = (Box*)objB;

	Vec2 circlePos = circleA->GetPosition();

	Vec2 nearestPointOnBox = Vec2(Clamp(circlePos.x, boxB->GetMinX(), boxB->GetMaxX()), Clamp(circlePos.y, boxB->GetMinY(), boxB->GetMaxY()));

	Vec2 displacement = nearestPointOnBox - circlePos;
	float distance = displacement.GetMagnitude();

	collInfo.objA = circleA;
	collInfo.objB = boxB;
	collInfo._overlapNormal = displacement.Normalise();
	collInfo._overlapAmount = distance - circleA->GetRadius();
	collInfo._overlapping = collInfo._overlapAmount < 0;

	if (collInfo._overlapping)
	{
		std::cout << "Circle to Box" << std::endl;
	}

	return collInfo;
}
CollisionInfo CircleToPlane(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Circle* circleA = (Circle*)objA;
	Plane* planeB = (Plane*)objB;

	float distance = Dot(circleA->GetPosition(), planeB->GetUnitNormal()) - planeB->GetDistanceFromOrigin();
	float overlapAmount = distance - circleA->GetRadius();

	collInfo.objA = circleA;
	collInfo.objB = planeB;
	collInfo._overlapNormal = planeB->GetUnitNormal();
	collInfo._overlapAmount = distance - circleA->GetRadius();
	collInfo._overlapping = collInfo._overlapAmount < 0;
	return collInfo;
}
CollisionInfo BoxToCircle(PhysicsObject* objA, PhysicsObject* objB)
{
	return CircleToBox(objB, objA);
}
CollisionInfo BoxToBox(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Box* boxA = (Box*)objA;
	Box* boxB = (Box*)objB;

	float distances[4];
	Vec2 normals[4] = { Vec2(1, 0), Vec2(-1, 0), Vec2(0, 1), Vec2(0, -1) };

	distances[0] = boxB->GetMaxX() - boxA->GetMinX();
	distances[1] = boxA->GetMaxX() - boxB->GetMinX();
	distances[2] = boxB->GetMaxY() - boxA->GetMinY();
	distances[3] = boxA->GetMaxY() - boxB->GetMinY();

	float smallestOverlap = distances[0];
	int smallestOverlapIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		if (distances[i] < smallestOverlap)
		{
			smallestOverlap = distances[i];
			smallestOverlapIndex = i;
		}
	}

	collInfo.objA = boxA;
	collInfo.objB = boxB;
	collInfo._overlapNormal = normals[smallestOverlapIndex];
	collInfo._overlapAmount = distances[smallestOverlapIndex];
	collInfo._overlapping = collInfo._overlapAmount > 0;

	if (collInfo._overlapping)
	{
		std::cout << "Box To Box" << std::endl;
	}

	return collInfo;
}
CollisionInfo BoxToPlane(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Box* boxA = (Box*)objA;
	Plane* planeB = (Plane*)objB;

	Vec2 points[4] = {
		Vec2(boxA->GetMinX(), boxA->GetMaxY()),
		Vec2(boxA->GetMaxX(), boxA->GetMaxY()),
		Vec2(boxA->GetMaxX(), boxA->GetMinY()),
		Vec2(boxA->GetMinX(), boxA->GetMinY())
	};

	float distances[4];

	distances[0] = Dot(points[0], planeB->GetUnitNormal()) - planeB->GetDistanceFromOrigin();
	distances[1] = Dot(points[1], planeB->GetUnitNormal()) - planeB->GetDistanceFromOrigin();
	distances[2] = Dot(points[2], planeB->GetUnitNormal()) - planeB->GetDistanceFromOrigin();
	distances[3] = Dot(points[3], planeB->GetUnitNormal()) - planeB->GetDistanceFromOrigin();

	float largestDistance = distances[0];
	int largestOverlapIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		if (distances[i] > largestDistance)
		{
			largestDistance = distances[i];
			largestOverlapIndex = i;
		}
	}

	collInfo.objA = boxA;
	collInfo.objB = planeB;
	collInfo._overlapNormal = planeB->GetUnitNormal();
	collInfo._overlapAmount = distances[largestOverlapIndex] - planeB->GetDistanceFromOrigin();
	collInfo._overlapping = collInfo._overlapAmount > 0;
	return collInfo;
}
CollisionInfo PlaneToCircle(PhysicsObject* objA, PhysicsObject* objB)
{
	return CircleToPlane(objB, objA);
}
CollisionInfo PlaneToBox(PhysicsObject* objA, PhysicsObject* objB)
{
	return BoxToPlane(objB, objA);
}
CollisionInfo PlaneToPlane(PhysicsObject* objA, PhysicsObject* objB)
{
	return CollisionInfo();
}
