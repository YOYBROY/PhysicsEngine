#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "CollisionInfo.h"
#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"

PhysicsEngine::PhysicsEngine()
{
	//appInfo.fixedFramerate = 1;
	appInfo.appName = "Physics Engine";
}

void PhysicsEngine::Initialise()
{
	PopulateCollisionFunctionArray();
	//Draw Box
	//_physicsObjects.push_back(new Circle(Vec2(-2, -1), 1, 1, 1));
	//_physicsObjects.push_back(new Circle(Vec2(-2, -1), 1, 1, 1));

	//Draw Box
	_physicsObjects.push_back(new Box(Vec2(3, 3), 3, 1, 1, 1));
	//_physicsObjects.push_back(new Box(Vec2(1.2f, 0), 2, 1.5f, 1, 1));

	//Draw Plane
	_physicsObjects.push_back(new Plane(Vec2(1, 0.4f), 0, 5));
}

void PhysicsEngine::Update(float delta)
{
	//Update Objects
	for (PhysicsObject* objects : _physicsObjects)
	{
		objects->Update(delta);
	}

	_physicsObjects[0]->SetPosition(cursorPos);

	//Resolve
	for (int i = 0; i < _physicsObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < _physicsObjects.size(); j++)
		{
			CollisionInfo collisionInfo = CheckCollision(_physicsObjects[i], _physicsObjects[j]);
			if (collisionInfo.objA == nullptr || collisionInfo.objB == nullptr) continue;

			if (collisionInfo._overlapping)
			{
				collisionInfo.objA->AddCollisionAccumulation(1);
				collisionInfo.objB->AddCollisionAccumulation(1);
			}
		}
	}

	for (PhysicsObject* objects : _physicsObjects)
	{
		objects->Draw(lines);
	}
}