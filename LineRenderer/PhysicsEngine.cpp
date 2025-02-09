#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "CollisionInfo.h"
#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"

PhysicsEngine::PhysicsEngine()
{
	appInfo.appName = "Physics Engine";
}

void PhysicsEngine::Initialise()
{
	//Draw Circle
	//_physicsObjects.push_back(new Circle(Vec2(0, 0), 1, 1, 1));
	_physicsObjects.push_back(new Circle(Vec2(1.2f, 3), 1, 1, 1));

	//Draw Box
	_physicsObjects.push_back(new Box(Vec2(1.2f, 3), 2, 1.5f, 1, 1));
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
			CollisionInfo collisionInfo = CircleToCircle(_physicsObjects[i], _physicsObjects[j]);

			if (collisionInfo._overlapping)
			{
				_physicsObjects[i]->SetColour(Colour::RED);
				_physicsObjects[j]->SetColour(Colour::RED);
			}
			else
			{
				_physicsObjects[i]->SetColour(Colour::GREEN);
				_physicsObjects[j]->SetColour(Colour::GREEN);
			}
		}
	}

	for (PhysicsObject* objects : _physicsObjects)
	{
		objects->Draw(lines);
	}
}