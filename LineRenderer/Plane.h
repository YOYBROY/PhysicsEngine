#pragma once

#include "PhysicsObject.h"

class Plane : public PhysicsObject
{
protected:
	Vec2 _unitNormal;
	float _distanceFromOrigin;
	float _length;

	ObjectType _objectType = PLANE;

public:
	Plane(Vec2 unitNormal, float distanceFromOrigin);
	Plane(Vec2 unitNormal, float distanceFromOrigin, float length);
	void Update(float delta) override;
	void Draw(LineRenderer* lines) override;
	ObjectType GetObjectType() override { return _objectType; }


	Vec2 GetUnitNormal() { return _unitNormal; }
	float GetDistanceFromOrigin() { return _distanceFromOrigin; }
	float GetLength() { return _length; }
};

