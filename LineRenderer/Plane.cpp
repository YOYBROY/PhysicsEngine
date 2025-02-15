#include "Plane.h"

Plane::Plane(Vec2 unitNormal, float distanceFromOrigin) : _unitNormal(unitNormal.Normalise()), _distanceFromOrigin(distanceFromOrigin)
{
	_elasticity = 1;
}

Plane::Plane(Vec2 unitNormal, float distanceFromOrigin, float length) : _unitNormal(unitNormal.Normalise()), _distanceFromOrigin(distanceFromOrigin), _length(length)
{
	_elasticity = 1;
}

void Plane::Update(float delta)
{
}

void Plane::Draw(LineRenderer* lines)
{
	Vec2 planeCenter = _unitNormal * _distanceFromOrigin;
	Vec2 perpendicularToUnitVector = Vec2(_unitNormal.y, -_unitNormal.x);
	Vec2 point1;
	Vec2 point2;
	if (abs(_length) > 0)
	{
		point1 = planeCenter + perpendicularToUnitVector * _length;
		point2 = planeCenter - perpendicularToUnitVector * _length;
	}
	else 
	{
		point1 = planeCenter + perpendicularToUnitVector * 50000;
		point2 = planeCenter - perpendicularToUnitVector * 50000;
	}
	
	lines->DrawLineSegment(point1, point2);
	lines->DrawLineWithArrow(planeCenter, _unitNormal + planeCenter);
}