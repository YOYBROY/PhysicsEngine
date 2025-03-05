#include "CuttingPolygons.h"
#include "Application.h"
#include "Polygon.h"

void CuttingPolygons::TryCut(Vec2 mousePos, std::vector<PhysicsObject*> bodies)
{
	if (cutting)
	{
		//do a collision check against the plane
		for (int i = 0; i < bodies.size(); i++)
		{
			Polygon* polyA = (Polygon*)bodies[i];
			polyA->GetWorldSpaceVertices();

		}
		
		//if all vertices are positive or all negative then there is no intersection
		//otherwise there is a cut, perform cut



		cutting = false;
	}
	else
	{
		point1 = mousePos;
		cutting = true;
	}
}

void CuttingPolygons::Draw(LineRenderer* lines, Vec2 cursorPos)
{
	if (cutting)
	{
		lines->DrawLineSegment(point1, cursorPos);
	}
}
