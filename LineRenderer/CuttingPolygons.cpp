#include "CuttingPolygons.h"
#include "Application.h"
#include "Polygon.h"
#include "PhysicsEngine.h"
#include <vector>

void CuttingPolygons::TryCut(Vec2 cursorPos, std::vector<PhysicsObject*>& bodies)
{
	if (cutting)
	{
		//do a collision check against the plane
		for (int i = bodies.size() - 1; i >= 0; i--)
		{
			Polygon* polyA = (Polygon*)bodies[i];
			std::vector<Vec2> verts = polyA->GetWorldSpaceVertices();

			Vec2 normal = (cursorPos - point1).GetNormalised().GetRotatedBy90();

			float lineProjectionLength = Dot(point1, normal);

			for (int j = 0; j < verts.size(); j++)
			{
				projectionDepths.push_back(Dot(verts[j], normal) - lineProjectionLength);
			}

			for (int j = 0; j < verts.size(); j++)
			{
				float next = 0;
				if (j == verts.size() - 1) next = 0;
				else next = j + 1;

				if (projectionDepths[j] < 0 && projectionDepths[next] > 0 || projectionDepths[j] > 0 && projectionDepths[next] < 0)
				{
					cuttingEdges.push_back(Vec2(j, next));
				}
			}

			if(cuttingEdges.size() == 0) continue;

			for (int j = 0; j < cuttingEdges.size(); j++)
			{
				Vec2 edgeVerts = cuttingEdges[j];
				cutPoints.push_back(RemapFromFloatToVec2(lineProjectionLength, projectionDepths[edgeVerts.x] + lineProjectionLength, projectionDepths[edgeVerts.y] + lineProjectionLength, verts[edgeVerts.y], verts[edgeVerts.x]));
			}

			std::vector<Vec2> poly1Verts;
			std::vector<Vec2> poly2Verts;
			int runningIndex = 0;

			//For poly 1 verts
			for (runningIndex; runningIndex < verts.size(); runningIndex++)
			{
				if (runningIndex < cuttingEdges[0].x )
				{
					poly1Verts.push_back(verts[runningIndex]);
				}
				else if (runningIndex == cuttingEdges[0].x)
				{
					poly1Verts.push_back(verts[runningIndex]);
					poly1Verts.push_back(cutPoints[0]);
					poly1Verts.push_back(cutPoints[1]);
				}
				else if (runningIndex == cuttingEdges[1].x)
				{
					poly2Verts.push_back(verts[runningIndex]);
					poly2Verts.push_back(cutPoints[1]);
					poly2Verts.push_back(cutPoints[0]);
				}
				else if(runningIndex >= cuttingEdges[0].y)
				{
					poly2Verts.push_back(verts[runningIndex]);
				}
				else if (runningIndex >= cuttingEdges[1].y)
				{
					poly1Verts.push_back(verts[runningIndex]);
				}
			}

			Vec2 totalPos1;
			for (int j = 0; j < poly1Verts.size(); j++)
			{
				totalPos1 += poly1Verts[j];
			}
			Vec2 midPoint1 = totalPos1 / poly1Verts.size();

			for (int j = 0; j < poly1Verts.size(); j++)
			{
				poly1Verts[j] -= midPoint1;
			}

			Vec2 totalPos2;
			for (int j = 0; j < poly2Verts.size(); j++)
			{
				totalPos2 += poly2Verts[j];
			}
			Vec2 midPoint2 = totalPos2 / poly2Verts.size();

			for (int j = 0; j < poly2Verts.size(); j++)
			{
				poly2Verts[j] -= midPoint2;
			}


			//if all vertices are positive or all negative then there is no intersection
			//otherwise there is a cut, perform cut

			
			Vec2 position = bodies[i]->GetPosition();

			Polygon* newPoly1 = new Polygon(midPoint1, poly1Verts.size(), 0.5, 1, 1);
			newPoly1->SetVertices(poly1Verts);

			Polygon* newPoly2 = new Polygon(midPoint2, poly2Verts.size(), 0.5, 1, 1);
			newPoly2->SetVertices(poly2Verts);

			bodies.push_back(newPoly1);
			bodies.push_back(newPoly2);

			bodies.erase(bodies.begin() + i);
		}
		
		

		cutting = false;
	}
	else
	{
		point1 = cursorPos;
		cutting = true;
	}
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
	if (cutPoints.size() > 0)
	{
		for (Vec2 cuttingPoints : cutPoints)
		{
			lines->DrawCircle(cuttingPoints, 0.1f);
		}
	}

}

Vec2 CuttingPolygons::RemapFromFloatToVec2(float value, float aMin, float aMax, Vec2 bMin, Vec2 bMax)
{
	Vec2 remapped;

	remapped.x = bMax.x + (bMin.x - bMax.x) * ((value - aMin) / (aMax - aMin));
	remapped.y = bMax.y + (bMin.y - bMax.y) * ((value - aMin) / (aMax - aMin));

	return remapped;
}

void PhysicsEngine::CutPolygons(int polyToRemove, std::vector<Vec2> poly1Verts, std::vector<Vec2> poly2Verts)
{
	
}