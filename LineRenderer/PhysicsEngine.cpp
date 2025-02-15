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
	//Draw Circle
	_physicsObjects.push_back(new Circle(Vec2(2, -1), 1, 1, 1, Vec2(-8, 0)));
	_physicsObjects.push_back(new Circle(Vec2(-2, -1), 2, 5, 1, Vec2(20, 0)));

	//Draw Box
	_physicsObjects.push_back(new Box(Vec2(3, 3), 3, 1, 4, 1, Vec2(-5,0)));
	_physicsObjects.push_back(new Box(Vec2(-3, 3), 2, 1.5f, 2, 1, Vec2(10, 0)));
	_physicsObjects.push_back(new Box(Vec2(0, -4), 10, 2, 1, 1, Vec2(0, 0)));

	//Draw Perfectly Square Box with Planes
	//_physicsObjects.push_back(new Plane(Vec2(0, 1), -8));
	//_physicsObjects.push_back(new Plane(Vec2(0, -1), -8));
	//_physicsObjects.push_back(new Plane(Vec2(1, 0), -8));
	//_physicsObjects.push_back(new Plane(Vec2(-1, 0), -8));

	//Draw Off axis box
	_physicsObjects.push_back(new Plane(Vec2(0.3f, 1), -8));
	_physicsObjects.push_back(new Plane(Vec2(-0.3f, -1), -8));
	_physicsObjects.push_back(new Plane(Vec2(1, -0.3f), -8));
	_physicsObjects.push_back(new Plane(Vec2(-1, 0.3f), -8));
}

void PhysicsEngine::Update(float delta)
{
	//Update Objects
	for (PhysicsObject* objects : _physicsObjects)
	{
		objects->Update(delta);
	}

	for (int i = 0; i < _physicsObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < _physicsObjects.size(); j++)
		{
			CollisionInfo collisionInfo = CheckCollision(_physicsObjects[i], _physicsObjects[j]);
			if (collisionInfo.objA == nullptr || collisionInfo.objB == nullptr) continue;
			if (collisionInfo._overlapping)
			{
				collisionInfo.Resolve();
			}
		}
	}

	for (PhysicsObject* objects : _physicsObjects)
	{
		objects->Draw(lines);
	}
}