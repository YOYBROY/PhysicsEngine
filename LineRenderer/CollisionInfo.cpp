#include "CollisionInfo.h"
#include "PhysicsObject.h"
#include "Player.h"


void CollisionInfo::Resolve()
{
	//float depenAmount = _overlapAmount - SKIN_THICKNESS;
	//
	//if (depenAmount < 0.0f) return;

	if (objB->GetMass() <= 0 && objA->GetMass() <= 0) return;
	if (objB->GetMass() <= 0)
	{
		float impulseMag = Dot(-(1 + objA->GetElasticity()) * objA->GetVelocity(), _overlapNormal) * objA->GetMass();
		objA->GetPosition() += _overlapNormal * _overlapAmount;
		objA->AddImpulse(_overlapNormal * impulseMag);
		return;
	}
	
	if (objA->GetMass() <= 0)
	{
		float impulseMag = Dot(-(1 + objB->GetElasticity()) * objB->GetVelocity(), _overlapNormal) * objB->GetMass();
		objB->GetPosition() -= _overlapNormal * _overlapAmount;
		objB->AddImpulse(_overlapNormal * impulseMag);
		return;
	}
	
	float totalInverseMass = objA->GetInverseMass() + objB->GetInverseMass();
	
	objA->GetPosition() += _overlapNormal * _overlapAmount * objA->GetInverseMass() / totalInverseMass;
	objB->GetPosition() -= _overlapNormal * _overlapAmount * objB->GetInverseMass() / totalInverseMass;
	
	//Coefficient of Restitution
	
	Vec2 relativeVelocity = objB->GetVelocity() - objA->GetVelocity();
	float relativeElasticity = objA->GetElasticity() * objB->GetElasticity();
	float relativeNormalVelocity = Dot(-(1 + relativeElasticity) * relativeVelocity, _overlapNormal);
	//if (relativeNormalVelocity > 0.0f)
	//{
		float impulseMag = relativeNormalVelocity / totalInverseMass;
		objA->AddImpulse(-_overlapNormal * impulseMag);
		objB->AddImpulse(_overlapNormal * impulseMag);
	//}
	
	objA->SetColour(Colour::RED);
	objB->SetColour(Colour::RED);
}