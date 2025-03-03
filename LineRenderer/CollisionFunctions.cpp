#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"
#include "Polygon.h"
#include "Player.h"
#include "LineRenderer.h"

#include<iostream>
#include <vector>

void PopulateCollisionFunctionArray()
{
	collisionThings[CIRCLE][CIRCLE] = CircleToCircle;
	collisionThings[CIRCLE][PLANE] = CircleToPlane;
	collisionThings[CIRCLE][POLYGON] = CircleToPolygon;
	//collisionThings[CIRCLE][PLAYER] = CircleToPlayer;

	collisionThings[PLANE][CIRCLE] = PlaneToCircle;
	collisionThings[PLANE][PLANE] = PlaneToPlane;
	collisionThings[PLANE][POLYGON] = PlaneToPolygon;
	//collisionThings[PLANE][PLAYER] = PlaneToPlayer;

	collisionThings[POLYGON][CIRCLE] = PolygonToCircle;
	collisionThings[POLYGON][PLANE] = PolygonToPlane;
	collisionThings[POLYGON][POLYGON] = PolygonToPolygon;
	collisionThings[POLYGON][PLAYER] = PolygonToPlayer;

	//collisionThings[PLAYER][CIRCLE] = PlayerToCircle;
	//collisionThings[PLAYER][PLANE] = PlayerToPlane;
	collisionThings[PLAYER][POLYGON] = PlayerToPolygon;
	//collisionThings[PLAYER][PLAYER] = PlayerToPlane;
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

CollisionInfo PlaneToCircle(PhysicsObject* objA, PhysicsObject* objB)
{
	return CircleToPlane(objB, objA);
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
	collInfo._overlapNormal = -planeA->GetUnitNormal();
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
CollisionInfo PolygonToPolygon(PhysicsObject* objA, PhysicsObject* objB)
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
CollisionInfo PolygonToPlayer(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Polygon* polyA = (Polygon*)objA;
	Player* playerB = (Player*)objB;

	//Get all the possible normals to check
	std::vector<Vec2> projectionNormals;

	for (Vec2 aNormal : polyA->GetNormals())
	{
		projectionNormals.push_back(aNormal);
	}
	for (Vec2 bNormal : playerB->GetNormals())
	{
		projectionNormals.push_back(bNormal);
	}
	//Get all the vertices to project
	std::vector<Vec2> polyAVerts = polyA->GetWorldSpaceVertices();
	std::vector<Vec2> polyBVerts = playerB->GetWorldSpaceVertices();

	float smallestOverlap = FLT_MAX;
	int smallestOverlapNormalIndex = 0;

	Vec2 displacement = polyA->GetPosition() - playerB->GetPosition();

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
	collInfo.objB = playerB;
	collInfo._overlapNormal = projectionNormals[smallestOverlapNormalIndex];
	collInfo._overlapAmount = smallestOverlap;
	collInfo._overlapping = collInfo._overlapAmount > 0;
	return collInfo;
}

CollisionInfo PlayerToPolygon(PhysicsObject* objA, PhysicsObject* objB)
{
	return PolygonToPlayer(objB,objA);
}