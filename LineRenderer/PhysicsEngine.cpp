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
	//_physicsObjects.push_back(new Polygon(Vec2(3, 5), 4, 2, 4, 1, 20));
	//Create Newtons Cradle
	_physicsObjects.push_back(new Circle(Vec2(-3, 6), 2, 0, 0.9f));
	_physicsObjects.push_back(new Circle(Vec2(2, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	_physicsObjects.push_back(new Circle(Vec2(1, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	_physicsObjects.push_back(new Circle(Vec2(0, 0), 0.3f, 1, 0.9f, Vec2(0, 2))); //Asymmetrical Cradle with inconsistent mass
	_physicsObjects.push_back(new Circle(Vec2(-1, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	_physicsObjects.push_back(new Circle(Vec2(-2, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	_physicsObjects.push_back(new Circle(Vec2(-3, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	
	//Create Box
	_physicsObjects.push_back(new Box(Vec2(1.6, 0.9), 1.6f, 0.9f, 1, 1, Vec2(-1.6f, -0.9f)));
	_physicsObjects.push_back(new Box(Vec2(-0.9*8, 1.6*4.5), 1.6f, 0.9f, 1, 1, Vec2(1.6f, -0.9f)));
	_physicsObjects.push_back(new Box(Vec2(6, 1.5), 3, 3, 0, 1));
	//_physicsObjects.push_back(new Box(Vec2(0, -4), 3, 2, 1, 1, Vec2(0, 0)));
	//_physicsObjects.push_back(new Polygon(Vec2(3, -5), 8, 2, 4, 1, 360/16));
	
	//Create Perfectly Square Box with Planes
	//_physicsObjects.push_back(new Plane(Vec2(1, 0), -8, 4.5f));
	//_physicsObjects.push_back(new Plane(Vec2(-1, 0), -8, 4.5f));
	//_physicsObjects.push_back(new Plane(Vec2(0, 1), -4.5f, 8));
	//_physicsObjects.push_back(new Plane(Vec2(0, -1), -4.5f, 8));
	
	//Create Polygons
	//_physicsObjects.push_back(new Polygon(Vec2(5, 7), 3, 1.0f, 1, 1, Vec2(1.2,-10)));
	//_physicsObjects.push_back(new Polygon(Vec2(2, 8), 4, 1.0f, 1, 1, Vec2(1.2,10)));

	//Create Off axis box
	_physicsObjects.push_back(new Plane(Vec2(0.5f, 0.5), -10));
	_physicsObjects.push_back(new Plane(Vec2(-0.5f, -0.5), -10));
	_physicsObjects.push_back(new Plane(Vec2(0.5, -0.5), -10));
	_physicsObjects.push_back(new Plane(Vec2(-0.5, 0.5), -10));
}

void PhysicsEngine::Update(float delta)
{
	//_physicsObjects[1]->SetPosition(cursorPos);

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