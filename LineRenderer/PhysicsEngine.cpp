#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "CollisionInfo.h"
#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"
#include "Polygon.h"
#include "Grid.h"

PhysicsEngine::PhysicsEngine()
{
	//appInfo.fixedFramerate = 1;
	appInfo.appName = "Physics Engine";
}

void PhysicsEngine::Initialise()
{
	PopulateCollisionFunctionArray();


	Grid level;
	level.LoadFromImage("Level1.png");

	_dynamicBodies.push_back(new Box(Vec2(3, 5), 1, 2, 1, 0));

	Vec2 runningPos;
	int runningCount = 0;

	for (int y = 0; y < level.GetHeight(); y++)
	{
		for (int x = 0; x < level.GetWidth(); x++)
		{
			if (level.At(x, y) == TileType::PLATFORM)
			{
				if (false)
				{
					//left
					if (x == 0)
					{
						_staticBodies.push_back(new Polygon(Vec2(x, -y + level.GetHeight() - 0.5), 2, 0.5, 0, 0.5f));
					}
					else if (level.At(x - 1, y) == TileType::EMPTY)
					{
						_staticBodies.push_back(new Polygon(Vec2(x, -y + level.GetHeight() - 0.5), 2, 0.5, 0, 0.5f));
					}
					//right
					if (x == level.GetWidth() - 1)
					{
						_staticBodies.push_back(new Polygon(Vec2(x + 1, -y + level.GetHeight() - 0.5), 2, 0.5, 0, 1));
					}
					else if (level.At(x + 1, y) == TileType::EMPTY)
					{
						_staticBodies.push_back(new Polygon(Vec2(x + 1, -y + level.GetHeight() - 0.5), 2, 0.5, 0, 1));
					}
					//up
					if (y == 0)
					{
						_staticBodies.push_back(new Polygon(Vec2(x + 0.5, -y + level.GetHeight()), 2, 0.5, 0, 1, 90));
					}
					else if (level.At(x, y - 1) == TileType::EMPTY)
					{
						_staticBodies.push_back(new Polygon(Vec2(x + 0.5, -y + level.GetHeight()), 2, 0.5, 0, 1, 90));
					}
					//down
					if (y == level.GetHeight() - 1)
					{
						_staticBodies.push_back(new Polygon(Vec2(x + 0.5, -y + level.GetHeight() - 1), 2, 0.5, 0, 1, 90));
					}
					else if (level.At(x, y + 1) == TileType::EMPTY)
					{
						_staticBodies.push_back(new Polygon(Vec2(x + 0.5, -y + level.GetHeight() - 1), 2, 0.5, 0, 1, 90));
					}
				}
				
				if (runningCount == 0)
				{
					runningPos = Vec2(x, y);
				}
				runningCount++;
				
				if (x == level.GetWidth() - 1)
				{
					//end run and create box
					Box* newPlatform = new Box(Vec2(runningPos.x + (runningCount * 0.5f), -y + level.GetHeight() - 0.5f), runningCount, 1, 0, 1);
					newPlatform->SetVisible(false);
					_staticBodies.push_back(newPlatform);
					runningCount = 0;
					runningPos = Vec2(0, 0);
				}
				//_staticBodies.push_back(new Box(Vec2(x + 0.5f, -y + level.GetHeight() - 0.5f), 1, 1, 0, 1));
			}
			else 
			{
				Box* newPlatform = new Box(Vec2(runningPos.x + (runningCount * 0.5f), -y + level.GetHeight() - 0.5f), runningCount, 1, 0, 1);
				newPlatform->SetVisible(false);
				_staticBodies.push_back(newPlatform);
				runningCount = 0;
				runningPos = Vec2(0, 0);
			}
		}
	}

	//Create Newtons Cradle
	//_physicsObjects.push_back(new Circle(Vec2(-3, 6), 2, 0, 0.9f));
	//_physicsObjects.push_back(new Circle(Vec2(2, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	//_physicsObjects.push_back(new Circle(Vec2(1, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	//_physicsObjects.push_back(new Circle(Vec2(0, 0), 0.3f, 1, 0.9f, Vec2(0, 2))); //Asymmetrical Cradle with inconsistent mass
	//_physicsObjects.push_back(new Circle(Vec2(-1, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	//_physicsObjects.push_back(new Circle(Vec2(-2, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));
	//_physicsObjects.push_back(new Circle(Vec2(-3, 0), 0.3f, 1, 0.9f, Vec2(0, 2)));

	//Create Box
	//_physicsObjects.push_back(new Box(Vec2(1.6, 0.9), 1.6f, 0.9f, 1, 1, Vec2(-1.6f, -0.9f)));
	//_physicsObjects.push_back(new Box(Vec2(-0.9*8, 1.6*4.5), 1.6f, 0.9f, 1, 1, Vec2(1.6f, -0.9f)));
	//_physicsObjects.push_back(new Box(Vec2(6, 1.5), 3, 3, 0, 1));
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
	//_physicsObjects.push_back(new Plane(Vec2(0.5f, 0.5), -10));
	//_physicsObjects.push_back(new Plane(Vec2(-0.5f, -0.5), -10));
	//_physicsObjects.push_back(new Plane(Vec2(0.5, -0.5), -10));
	//_physicsObjects.push_back(new Plane(Vec2(-0.5, 0.5), -10));
}

void PhysicsEngine::Update(float delta)
{
	//_physicsObjects[1]->SetPosition(cursorPos);

	//Update Objects
	for (PhysicsObject* objects : _dynamicBodies)
	{
		objects->Update(delta);
	}
	for (int i = 0; i < _dynamicBodies.size() - 1; i++)
	{
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

	for (int i = 0; i < _staticBodies.size() - 1; i++)
	{
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
}