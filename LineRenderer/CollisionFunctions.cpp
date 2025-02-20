#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"
#include "Polygon.h"
#include "LineRenderer.h"

#include<iostream>
#include <vector>

void PopulateCollisionFunctionArray()
{
	collisionThings[CIRCLE][CIRCLE] = CircleToCircle;
	collisionThings[CIRCLE][BOX] = CircleToBox;
	collisionThings[CIRCLE][PLANE] = CircleToPlane;
	collisionThings[CIRCLE][POLYGON] = CircleToPolygon;

	collisionThings[BOX][CIRCLE] = BoxToCircle;
	collisionThings[BOX][BOX] = BoxToBox;
	collisionThings[BOX][PLANE] = BoxToPlane;
	//collisionThings[BOX][POLYGON] = BoxToPolygon;

	collisionThings[PLANE][CIRCLE] = PlaneToCircle;
	collisionThings[PLANE][BOX] = PlaneToBox;
	collisionThings[PLANE][PLANE] = PlaneToPlane;
	collisionThings[PLANE][POLYGON] = PlaneToPolygon;

	collisionThings[POLYGON][CIRCLE] = PolygonToCircle;
	//collisionThings[POLYGON][BOX] = PolygonToBox;
	collisionThings[POLYGON][PLANE] = PolygonToPlane;
	collisionThings[POLYGON][POLYGON] = PolygonToPolgon;
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

	Vec2 displacement = circleB->GetPosition() - circleA->GetPosition();
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
	collInfo._overlapNormal = -planeB->GetUnitNormal();
	collInfo._overlapAmount = distance - circleA->GetRadius();
	collInfo._overlapping = collInfo._overlapAmount < 0;
	return collInfo;
}
CollisionInfo CircleToPolygon(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Circle* circleA = (Circle*)objA;
	Polygon* polyB = (Polygon*)objB;

	//Get all the possible normals to check
	std::vector<Vec2> projectionNormals;

	for (Vec2 bNormal : polyB->GetNormals())
	{
		projectionNormals.push_back(bNormal);
	}
	for (Vec2 vertex : polyB->GetWorldSpaceVertices())
	{
		projectionNormals.push_back((circleA->GetPosition() - vertex).Normalise());
	}

	//Get all the vertices to project
	std::vector<Vec2> polyBVerts = polyB->GetWorldSpaceVertices();

	float smallestOverlap = FLT_MAX;
	int smallestOverlapNormalIndex = 0;

	Vec2 displacement = circleA->GetPosition() - polyB->GetPosition();
	//Project all the vertices on to every normal
	//Find the min and max distances for each polygon
	for (int i = 0; i < projectionNormals.size(); i++)
	{
		if (Dot(displacement.Normalise(), projectionNormals[i]) < 0) continue;
		float circleAMin = Dot(circleA->GetPosition(), projectionNormals[i]) - circleA->GetRadius();
		float circleAMax = Dot(circleA->GetPosition(), projectionNormals[i]) + circleA->GetRadius();
		float polyBMin = FLT_MAX;
		float polyBMax = -FLT_MAX;

		for (int j = 0; j < polyBVerts.size(); j++)
		{
			float projectionLength = Dot(polyBVerts[j], projectionNormals[i]);
			polyBMax = projectionLength > polyBMax ? projectionLength : polyBMax;
			polyBMin = projectionLength < polyBMin ? projectionLength : polyBMin;
		}

		float overlap1 = circleAMax - polyBMin;
		float overlap2 = polyBMax - circleAMin;
		float localSmallestOverlap = overlap1 < overlap2 ? overlap1 : overlap2;

		if (localSmallestOverlap < smallestOverlap)
		{
			smallestOverlap = localSmallestOverlap;
			smallestOverlapNormalIndex = i;
		}
	}

	collInfo.polygonVertices = polyB->GetWorldSpaceVertices();
	collInfo.objA = circleA;
	collInfo.objB = polyB;
	collInfo._overlapNormal = projectionNormals[smallestOverlapNormalIndex];
	//collInfo._overlapNormal = displacement.Normalise();
	collInfo._overlapAmount = smallestOverlap;
	collInfo._overlapping = collInfo._overlapAmount > 0;
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
		if (distances[i] < largestDistance)
		{
			largestDistance = distances[i];
			largestOverlapIndex = i;
		}
	}
	collInfo._closestPoint = points[largestOverlapIndex];
	collInfo.objA = boxA;
	collInfo.objB = planeB;
	collInfo._overlapNormal = -planeB->GetUnitNormal();
	collInfo._overlapAmount = distances[largestOverlapIndex];
	collInfo._overlapping = collInfo._overlapAmount < 0;
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

CollisionInfo PlaneToPolygon(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Plane* planeA = (Plane*)objA;
	Polygon* polyB = (Polygon*)objB;

	//Get all the vertices to project
	std::vector<Vec2> polyBVerts = polyB->GetWorldSpaceVertices();

	float smallestOverlap = FLT_MAX;
	int smallestOverlapNormalIndex = 0;

	//Project all the vertices on to every normal
	//Find the min and max distances for each polygon
	float AMin = -FLT_MAX;
	float AMax = planeA->GetDistanceFromOrigin();
	float polyBMin = FLT_MAX;
	float polyBMax = -FLT_MAX;

	for (int j = 0; j < polyBVerts.size(); j++)
	{
		float projectionLength = Dot(polyBVerts[j], planeA->GetUnitNormal());
		polyBMax = projectionLength > polyBMax ? projectionLength : polyBMax;
		polyBMin = projectionLength < polyBMin ? projectionLength : polyBMin;
	}

	float overlap1 = AMax - polyBMin;
	float overlap2 = polyBMax - AMin;
	float localSmallestOverlap = overlap1 < overlap2 ? overlap1 : overlap2;

	if (localSmallestOverlap < smallestOverlap)
	{
		smallestOverlap = localSmallestOverlap;
	}

	collInfo.objA = planeA;
	collInfo.objB = polyB;
	collInfo._overlapNormal = planeA->GetUnitNormal();
	collInfo._overlapAmount = smallestOverlap;
	collInfo._overlapping = collInfo._overlapAmount > 0;
	return collInfo;
}

CollisionInfo PolygonToCircle(PhysicsObject* objA, PhysicsObject* objB)
{
	return CircleToPolygon(objB, objA);
}


CollisionInfo PolygonToPlane(PhysicsObject* objA, PhysicsObject* objB)
{
	return PlaneToPolygon(objB, objA);
}
CollisionInfo PolygonToPolgon(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Polygon* polyA = (Polygon*)objA;
	Polygon* polyB = (Polygon*)objB;

	//Get all the possible normals to check
	std::vector<Vec2> projectionNormals;

	for (Vec2 aNormal : polyA->GetNormals())
	{
		projectionNormals.push_back(aNormal);
	}
	for (Vec2 bNormal : polyB->GetNormals())
	{
		projectionNormals.push_back(bNormal);
	}
	//Get all the vertices to project
	std::vector<Vec2> polyAVerts = polyA->GetWorldSpaceVertices();
	std::vector<Vec2> polyBVerts = polyB->GetWorldSpaceVertices();

	float smallestOverlap = FLT_MAX;
	int smallestOverlapNormalIndex = 0;

	Vec2 displacement = polyA->GetPosition() - polyB->GetPosition();

	//Project all the vertices on to every normal
	//Find the min and max distances for each polygon
	for (int i = 0; i < projectionNormals.size(); i++)
	{
		if (Dot(displacement.Normalise(), projectionNormals[i]) < 0) continue;
		float polyAMin = FLT_MAX;
		float polyAMax = -FLT_MAX;
		float polyBMin = FLT_MAX;
		float polyBMax = -FLT_MAX;
		for (int j = 0; j < polyAVerts.size(); j++)
		{
			float projectionLength = Dot(polyAVerts[j], projectionNormals[i]);
			polyAMax = projectionLength > polyAMax ? projectionLength : polyAMax;
			polyAMin = projectionLength < polyAMin ? projectionLength : polyAMin;
		}
		for (int j = 0; j < polyBVerts.size(); j++)
		{
			float projectionLength = Dot(polyBVerts[j], projectionNormals[i]);
			polyBMax = projectionLength > polyBMax ? projectionLength : polyBMax;
			polyBMin = projectionLength < polyBMin ? projectionLength : polyBMin;
		}

		float overlap1 = polyAMax - polyBMin;
		float overlap2 = polyBMax - polyAMin;
		float localSmallestOverlap = overlap1 < overlap2 ? overlap1 : overlap2;

		if (localSmallestOverlap < smallestOverlap)
		{
			smallestOverlap = localSmallestOverlap;
			smallestOverlapNormalIndex = i;
		}
	}

	collInfo.objA = polyA;
	collInfo.objB = polyB;
	collInfo._overlapNormal = projectionNormals[smallestOverlapNormalIndex];
	collInfo._overlapAmount = smallestOverlap;
	collInfo._overlapping = collInfo._overlapAmount > 0;
	return collInfo;
}