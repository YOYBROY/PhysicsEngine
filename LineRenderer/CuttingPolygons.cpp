#include <vector>

#include "CuttingPolygons.h"
#include "Application.h"
#include "Polygon.h"
#include "PhysicsEngine.h"
#include "Utility.h"

void CuttingPolygons::TryCut(Vec2 cursorPos, std::vector<PhysicsObject*>& bodies)
{
	if (!cutting)
	{
		point1 = cursorPos;
		cutting = true;
		return;
	}

	//do a collision check against the plane
	for (int i = bodies.size() - 1; i >= 0; i--)
	{
		Polygon* polyA = (Polygon*)bodies[i];
		std::vector<Vec2> verts = polyA->GetWorldSpaceVertices();
		std::vector<Vec2> cuttingEdges;
		std::vector<float> projectionDepths;
		std::vector<Vec2> cutPoints;
		
		Vec2 normal = (cursorPos - point1).GetNormalised().GetRotatedBy90();

		float lineProjectionLength = Dot(point1, normal);

		for (Vec2 vertex : verts)
		{
			projectionDepths.push_back(Dot(vertex, normal) - lineProjectionLength);
		}

		for (int j = 0; j < projectionDepths.size(); j++)
		{
			int next = 0;
			if (j == projectionDepths.size() - 1) next = 0;
			else next = j + 1;

			if (projectionDepths[j] < 0 && projectionDepths[next] > 0 || projectionDepths[j] > 0 && projectionDepths[next] < 0)
			{
				cuttingEdges.push_back(Vec2(j, next));
			}
		}

		if (cuttingEdges.size() == 0) continue;

		for (Vec2 edgeVerts : cuttingEdges)
		{
			cutPoints.push_back(RemapFromFloatToVec2(lineProjectionLength, projectionDepths[edgeVerts.x] + lineProjectionLength, projectionDepths[edgeVerts.y] + lineProjectionLength, verts[edgeVerts.y], verts[edgeVerts.x]));
		}

		//Check to see if poly is within line
		//Vec2 newNormal = cursorPos - point1;
		//
		//float point1NormalProjection = Dot(point1, newNormal);
		//float point2NormalProjection = Dot(cursorPos, newNormal);
		//bool intersects = true;
		//
		//for (Vec2 vertex : cutPoints)
		//{
		//	float depth = Dot(vertex, newNormal);
		//	if (depth - point1NormalProjection < 0)
		//	{
		//		intersects = false;
		//	}
		//	else if (depth - point2NormalProjection > 0)
		//	{
		//		intersects = false;
		//	}
		//}
		//if (!intersects) break;

		std::vector<Vec2> poly1Verts;
		std::vector<Vec2> poly2Verts;

		//For poly 1 verts
		for (int j = 0; j < projectionDepths.size(); j++)
		{
			if (projectionDepths[j] > 0)
			{
				poly1Verts.push_back(verts[j]);
			}
			else
			{
				poly2Verts.push_back(verts[j]);
			}
		}

		poly1Verts.insert(poly1Verts.end(), cutPoints.begin(), cutPoints.end());
		poly2Verts.insert(poly2Verts.end(), cutPoints.begin(), cutPoints.end());

		Vec2 midPoint1 = GetMidpoint(poly1Verts);
		for (Vec2& vertex : poly1Verts)
		{
			vertex -= midPoint1;
		}
		Vec2 midPoint2 = GetMidpoint(poly2Verts);
		for (Vec2& vertex : poly2Verts)
		{
			vertex -= midPoint2;
		}

		//This does not work properly because the winding order can still go around clockwise and not go in a coherent order
		FixWindingOrder2(poly1Verts);
		FixWindingOrder2(poly2Verts);
		
		Vec2 velocity = bodies[i]->GetVelocity();
		float elasticity = bodies[i]->GetElasticity();
		float mass = bodies[i]->GetMass() * 0.5f;

		//Create an overload that creates arbitrary polygons
		Polygon* newPoly1 = new Polygon(midPoint1, poly1Verts.size(), 0.5, mass, elasticity, velocity);
		newPoly1->SetVertices(poly1Verts);

		Polygon* newPoly2 = new Polygon(midPoint2, poly2Verts.size(), 0.5, mass, elasticity, velocity);
		newPoly2->SetVertices(poly2Verts);

		bodies.push_back(newPoly1);
		bodies.push_back(newPoly2);

		bodies.erase(bodies.begin() + i);
	}
	cutting = false;
}

void CuttingPolygons::Draw(LineRenderer* lines, Vec2 cursorPos)
{
	if (cutting)
	{
		Vec2 midPoint = (point1 + cursorPos) * 0.5f;

		Vec2 normal = (cursorPos - point1).GetNormalised().GetRotatedBy90();

		lines->DrawLineSegment(point1, cursorPos);
		lines->DrawLineWithArrow(midPoint, midPoint + normal);
	}
}