#include "Platformer.h"
#include "PhysicsObject.h"
#include "Key.h"
#include "CollisionInfo.h"
#include "CollisionFunctions.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"
#include "Polygon.h"
#include "Grid.h"
#include "imgui.h"

Platformer::Platformer()
{
	//appInfo.fixedFramerate = 1;
	appInfo.appName = "Platformer";
	cameraHeight = 41.0f;
	appInfo.grid.show = false;
	appInfo.grid.extent = 100;
}

Platformer::~Platformer()
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

void Platformer::Initialise()
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
					//runningBoxType += 13;
				}
				else if (level.At(x - 1, y) != TileType::PLATFORM)
				{
					runningBoxType += 13;
				}
				//right
				if (x == level.GetWidth() - 1)
				{
					//runningBoxType += 7;
				}
				else if (level.At(x + 1, y) != TileType::PLATFORM)
				{
					runningBoxType += 7;
				}
				//up
				if (y == 0)
				{
					//runningBoxType += 3;
				}
				else if (level.At(x, y - 1) != TileType::PLATFORM)
				{
					runningBoxType += 3;
				}
				//down
				if (y == level.GetHeight() - 1)
				{
					//runningBoxType += 11;
				}
				else if (level.At(x, y + 1) != TileType::PLATFORM)
				{
					runningBoxType += (int)BoxType::D;
				}

				Box* newPlatform = new Box(Vec2(x + 0.5f, level.GetHeight() - y - 0.5f), 1.6f, 1, 0, 1);
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

void Platformer::Update(float delta)
{
	ImGui::Begin("Debug Window");

	//Player Parameters
	ImGui::Checkbox("Debug Player", &player->debug);
	if (player->debug)
	{
		if (ImGui::SliderFloat("Max Step", &player->maxStepHeight, 0.0f, 1.0f));
		if (ImGui::SliderFloat("Head Slip", &player->headSlip, 0.0f, 1.0f));
		if (ImGui::SliderFloat("Foot Slip", &player->footSlip, 0.0f, 1.0f));
		if (ImGui::SliderFloat("Umbrella Angle", &player->umbrellaAngle, 0.0f, 1.0f));
	}

	//Camera Options
	ImGui::Checkbox("Camera To Player", &cameraToPlayer);
	if (ImGui::SliderFloat("Camera Height", &cameraHeight, 5.0f, 60.0f));
	if (ImGui::SliderFloat("Camera Pos X", &cameraPosition.x, -60.0f, 60.0f));
	if (ImGui::SliderFloat("Camera Pos Y", &cameraPosition.y, -60.0f, 60.0f));

	ImGui::End();

	for (PhysicsObject* objects : _dynamicBodies)
	{
		objects->Update(delta);
	}
	
	player->HandleInput(delta);

	//Umbrella Mechanic
	if (!player->grounded && player->umbrella)
	{
		Vec2 umbrellaDirection = Vec2(0, 1).GetNormalised().RotateBy(DegToRad(player->umbrellaAngle));
		Vec2 velocityAgainstUmbrella = Dot(player->GetVelocity(), umbrellaDirection) * umbrellaDirection;

		if (Dot(player->GetVelocity().GetNormalised(), Vec2(0, 1)) < 0.5f)
		{
			player->AddForce(velocityAgainstUmbrella * -8);
		}

		lines->DrawLineSegment(player->GetPosition() + Vec2(0,1) + (umbrellaDirection.GetRotatedBy90() * 0.5f), player->GetPosition() + Vec2(0, 1) - (umbrellaDirection.GetRotatedBy90() * 0.5f));
	}

	player->grounded = false;

	cameraCentre = cameraToPlayer ? player->GetPosition() : cameraPosition;

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

void Platformer::OnKeyPress(Key key)
{
	if (key == Key::Space)
	{
		player->AttemptJump();
	}
}