#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"

CollisionInfo CircleToCircle(PhysicsObject* objA, PhysicsObject* objB)
{
    CollisionInfo collInfo;
    Circle* circleA = (Circle*)objA;
    Circle* circleB = (Circle*)objB;

    Vec2 displacement = circleA->GetPosition() - circleB->GetPosition();
    float distance = displacement.GetMagnitude();

    collInfo.objA = circleA;
    collInfo.objB = circleB;
    collInfo._overlapNormal = displacement.Normalise();
    collInfo._overlapAmount = distance - (circleA->GetRadius() + circleB->GetRadius());
    collInfo._overlapping = collInfo._overlapAmount < 0;

    return collInfo;
}

CollisionInfo CircleToBox(PhysicsObject* objA, PhysicsObject* objB)
{
	CollisionInfo collInfo;
	Circle* circleA = (Circle*)objA;
	Box* boxB = (Box*)objB;


	//DOING COLLKISIONS IN HERE ATM

	Vec2 displacement = circleA->GetPosition() - boxB->GetPosition();
	float distance = displacement.GetMagnitude();

	collInfo.objA = circleA;
	collInfo.objB = boxB;
	//collInfo._overlapNormal = minDisplacement.Normalise();
	//collInfo._overlapAmount = distance - (circleA->GetRadius() + boxB->GetRadius());
	collInfo._overlapping = collInfo._overlapAmount < 0;

	return collInfo;
}

//CollisionInfo CircleToBox(PhysicsObject* objA, PhysicsObject* objB)
//{
//    CollisionInfo collInfo;
//
//}