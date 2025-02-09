#include "Plane.h"

Plane::Plane(Vec2 unitNormal, float distanceFromOrigin) : _unitNormal(unitNormal.Normalise()), _distanceFromOrigin(distanceFromOrigin)
{
}

Plane::Plane(Vec2 unitNormal, float distanceFromOrigin, float length) : _unitNormal(unitNormal.Normalise()), _distanceFromOrigin(distanceFromOrigin), _length(length)
{
}

void Plane::Update(float delta)
{
}

void Plane::Draw(LineRenderer* lines)
{
	Vec2 planeCenter = _unitNormal * _distanceFromOrigin;
	Vec2 perpendicularToUnitVector = Vec2(_unitNormal.y, -_unitNormal.x);
	Vec2 point1 = planeCenter + perpendicularToUnitVector * _length;
	Vec2 point2 = planeCenter - perpendicularToUnitVector * _length;
	lines->DrawLineSegment(point1, point2);
	lines->DrawLineWithArrow(planeCenter, _unitNormal + planeCenter);
}