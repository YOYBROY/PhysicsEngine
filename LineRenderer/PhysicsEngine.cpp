#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "Key.h"
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
	appInfo.appName = "Platformer";
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

	Grid level;
	level.LoadFromImage("Level2.png");

	Vec2 runningPos;
	int runningCount = 0;
	Vec2 playerStart;

	for (int y = 0; y < level.GetHeight(); y++)
	{
		for (int x = 0; x < level.GetWidth(); x++)
		{
			if (level.At(x, y) == TileType::PLATFORM)
			{
				int runningBoxType = 0;
				//left
				if (x == 0)
				{
					runningBoxType += 13;
				}
				else if (level.At(x - 1, y) != TileType::PLATFORM)
				{
					runningBoxType += 13;
				}
				//right
				if (x == level.GetWidth() - 1)
				{
					runningBoxType += 7;
				}
				else if (level.At(x + 1, y) != TileType::PLATFORM)
				{
					runningBoxType += 7;
				}
				//up
				if (y == 0)
				{
					runningBoxType += 3;
				}
				else if (level.At(x, y - 1) != TileType::PLATFORM)
				{
					runningBoxType += 3;
				}
				//down
				if (y == level.GetHeight() - 1)
				{
					runningBoxType += 11;
				}
				else if (level.At(x, y + 1) != TileType::PLATFORM)
				{
					runningBoxType += (int)BoxType::D;
				}

				Box* newPlatform = new Box(Vec2(x + 0.5f, level.GetHeight() - y - 0.5f), 1, 1, 0, 1);
				newPlatform->SetBoxType(runningBoxType);
				_staticBodies.push_back(newPlatform);
				continue;
			}
			else if (level.At(x, y) == TileType::PLAYERSTART)
			{
				playerStart = Vec2(x + 0.5f, level.GetHeight() - y - 0.5f);
			}
		}
	}

	player = new Player(playerStart, 0.7f, 1, 1, 0);
	player->SetColour(Colour::BLUE);
	ObjectType type = player->GetObjectType();
	_dynamicBodies.push_back(player);
}

void PhysicsEngine::Update(float delta)
{
	cameraCentre = player->GetPosition();

	player->HandleInput();
	player->grounded = false;

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

void PhysicsEngine::OnKeyPress(Key key)
{
	if (key == Key::Space)
	{
		player->AttemptJump();
	}
}