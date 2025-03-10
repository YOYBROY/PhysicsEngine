#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "Key.h"
#include "CollisionInfo.h"
#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"
#include "Polygon.h"
#include "Imgui.h"

PhysicsEngine::PhysicsEngine()
{
	//appInfo.fixedFramerate = 1;
	appInfo.appName = "Physics Engine";
	appInfo.grid.show = false;
}

PhysicsEngine::~PhysicsEngine()
{
	for (PhysicsObject* thisBody : _dynamicBodies)
	{
		delete thisBody;
	}
	for (PhysicsObject* thisBody : _staticBodies)
	{
		delete thisBody;
	}
}

void PhysicsEngine::Initialise()
{
	PopulateCollisionFunctionArray();

	Polygon* newPlatform = new Polygon(Vec2(1, 1), 5, 1, 1, 0.8f);
	_dynamicBodies.push_back(newPlatform);
	
	newPlatform = new Polygon(Vec2(0.8, 2), 7, 1, 1, 0.8f);
	_dynamicBodies.push_back(newPlatform);
	newPlatform = new Polygon(Vec2(1.2, 4), 4, 1, 1, 0.8f);
	_dynamicBodies.push_back(newPlatform);
	newPlatform = new Polygon(Vec2(1.4, 8), 3, 1, 1, 0.8f);
	_dynamicBodies.push_back(newPlatform);

	_staticBodies.push_back(new Plane(Vec2(0, 1), -5));
	_staticBodies.push_back(new Plane(Vec2(1, 0), -8));
	_staticBodies.push_back(new Plane(Vec2(-1, 0), -8));
}

void PhysicsEngine::Update(float delta)
{
	for (PhysicsObject* objects : _dynamicBodies)
	{
		objects->Update(delta);
	}

	for (int i = 0; i < _dynamicBodies.size() - 1; i++)
	{
		if (_dynamicBodies.size() <= 0) break;
		for (int j = i + 1; j < _dynamicBodies.size(); j++)
		{
			CollisionInfo collisionInfo = CheckCollision(_dynamicBodies[i], _dynamicBodies[j]);
			if (collisionInfo.objA == nullptr || collisionInfo.objB == nullptr) continue;
			if (collisionInfo._overlapping)
			{
				collisionInfo.Resolve();
			}
		}
	}
	
	for (int i = 0; i < _staticBodies.size(); i++)
	{
		if (_staticBodies.size() <= 0) break;
		for (int j = 0; j < _dynamicBodies.size(); j++)
		{
			CollisionInfo collisionInfo = CheckCollision(_staticBodies[i], _dynamicBodies[j]);
			if (collisionInfo.objA == nullptr || collisionInfo.objB == nullptr) continue;
			if (collisionInfo._overlapping)
			{
				collisionInfo.Resolve();
			}
		}
	}

	for (PhysicsObject* objects : _staticBodies)
	{
		objects->Draw(lines);
	}
	for (PhysicsObject* objects : _dynamicBodies)
	{
		objects->Draw(lines);
	}
	cuttingPolygons.Draw(lines, cursorPos);
}

void PhysicsEngine::OnLeftClick()
{
	cuttingPolygons.TryCut(cursorPos, _dynamicBodies);
}

void PhysicsEngine::OnLeftRelease()
{
	cuttingPolygons.TryCut(cursorPos, _dynamicBodies);
}