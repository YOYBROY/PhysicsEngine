#include "Utility.h"
#include "AngleOrder.h"


Vec2 RemapFromFloatToVec2(float value, float aMin, float aMax, Vec2 bMin, Vec2 bMax)
{
	Vec2 remapped;

	remapped.x = bMax.x + (bMin.x - bMax.x) * ((value - aMin) / (aMax - aMin));
	remapped.y = bMax.y + (bMin.y - bMax.y) * ((value - aMin) / (aMax - aMin));

	return remapped;
}

Vec2 GetMidpoint(std::vector<Vec2> verts)
{
	Vec2 totalPos;
	for (int j = 0; j < verts.size(); j++)
	{
		totalPos += verts[j];
	}
	Vec2 midPoint = totalPos / verts.size();
	return midPoint;
}

void FixWindingOrder(std::vector<Vec2>& verts)
{
	for (int i = 0; i < verts.size(); i++)
	{
		int current = i;                                       //a
		int previous = (i - 1) < 0 ? verts.size() - 1 : i - 1; //b
		int next = (i + 1) % verts.size();                     //c

		Vec2 ab = verts[previous] - verts[current];
		Vec2 ac = verts[next] - verts[current];

		if (PseudoCross(ab, ac) < 0)
		{
			Vec2 temp = verts[next];
			verts[next] = verts[current];
			verts[current] = temp;
			FixWindingOrder(verts);
		}
	}
}

void FixWindingOrder2(std::vector<Vec2>& verts)
{
	std::vector<AngleOrder> angles;
	for (int i = 0; i < verts.size(); i++)
	{
		AngleOrder newAngle;
		newAngle.index = i;
		newAngle.angle = atan2(verts[i].y, verts[i].x);
		angles.push_back(newAngle);
	}

	for (int i = 0; i < angles.size(); i++)
	{
		for (int j = 0; j < angles.size(); j++)
		{
			if (angles[i].angle > angles[j].angle)
			{
				AngleOrder temp = angles[i];
				angles[i] = angles[j];
				angles[j] = temp;
			}
		}
	}

	std::vector<Vec2> newVertOrder;
	for (int i = 0; i < verts.size(); i++)
	{
		newVertOrder.push_back(verts[angles[i].index]);
	}
	verts = newVertOrder;
}