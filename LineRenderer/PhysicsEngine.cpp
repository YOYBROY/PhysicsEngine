#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "CollisionInfo.h"
#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"
#include "Polygon.h"

PhysicsEngine::PhysicsEngine()
{
	//appInfo.fixedFramerate = 1;
	appInfo.appName = "Physics Engine";
}

void PhysicsEngine::Initialise()
{
	PopulateCollisionFunctionArray();
	//Create Newtons Cradle
	_physicsObjects.push_back(new Circle(Vec2(4, 0), 0.3f, 1, 1, Vec2(-2, 0)));
	_physicsObjects.push_back(new Circle(Vec2(2, 0), 1.2f, 1, 1));
	_physicsObjects.push_back(new Circle(Vec2(1, 0), 0.3f, 1, 1));
	_physicsObjects.push_back(new Circle(Vec2(0, 0), 0.3f, 5, 1)); //Asymmetrical Cradle with inconsistent mass
	_physicsObjects.push_back(new Circle(Vec2(-1, 0), 0.3f, 1, 1));
	_physicsObjects.push_back(new Circle(Vec2(-2, 0), 0.3f, 1, 1));
	_physicsObjects.push_back(new Circle(Vec2(-3, 0), 0.3f, 1, 1));
	
	//_physicsObjects.push_back(new Circle(Vec2(-3, 0), 1, 1, 1));

	//Create Box
	//_physicsObjects.push_back(new Box(Vec2(1, 0.5f), 1, 1, 1, 0.5f));
	//_physicsObjects.push_back(new Box(Vec2(6, 1.5), 3, 3, 10, 0.4f, Vec2(-2, 0)));
	//_physicsObjects.push_back(new Box(Vec2(0, -4), 10, 2, 1, 1, Vec2(0, 0)));

	//Create Perfectly Square Box with Planes
	_physicsObjects.push_back(new Plane(Vec2(1, 0), -10));
	_physicsObjects.push_back(new Plane(Vec2(0, 1), -10));
	_physicsObjects.push_back(new Plane(Vec2(0, -1), -10));
	_physicsObjects.push_back(new Plane(Vec2(-1, 0), -10));

	//Create Polygons
	_physicsObjects.push_back(new Polygon(Vec2(5, 7), 3, 1.0f, 1, 1, Vec2(1.2,-10)));
	_physicsObjects.push_back(new Polygon(Vec2(2, 8), 4, 1.0f, 1, 1, Vec2(1.2,10)));
	_physicsObjects.push_back(new Polygon(Vec2(3, 5), 7, 2, 4, 1));
	
	//Create Off axis box
	//_physicsObjects.push_back(new Plane(Vec2(0.5f, 0.5), -10));
	//_physicsObjects.push_back(new Plane(Vec2(-0.5f, -0.5), -10));
	//_physicsObjects.push_back(new Plane(Vec2(0.5, -0.5), -10));
	//_physicsObjects.push_back(new Plane(Vec2(-0.5, 0.5), -10));
}

void PhysicsEngine::Update(float delta)
{
	//_physicsObjects[0]->SetPosition(cursorPos);

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

			//lines->DrawLineWithArrow(Vec2(), collisionInfo._overlapNormal);

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