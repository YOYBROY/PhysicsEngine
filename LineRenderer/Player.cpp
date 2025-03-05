#include "Player.h"

#include "TextStream.h"
#include "ApplicationHarness.h"
#include "Key.h"

Player::Player(Vec2 position, float width, float height, float mass, float elasticity) : Polygon(position, mass, elasticity), _width(width), _height(height)
{
	maxStepHeight = _height * maxStepFraction;
	footSlip = _width * footSlipFraction;
	headSlip = footSlip;

	float _maxX = +width * 0.5f;
	float _minX = -width * 0.5f;
	float _maxY = +height * 0.5f;
	float _minY = -height * 0.5f;

	_vertices.push_back(Vec2(_minX, _maxY));
	_vertices.push_back(Vec2(_maxX, _maxY));
	_vertices.push_back(Vec2(_maxX, _minY));
	_vertices.push_back(Vec2(_minX, _minY));

	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }

		_normals.push_back(Vec2(-(next.y - _vertices[i].y), next.x - _vertices[i].x).Normalise());
		_edgeCentres.push_back((_vertices[i] + next) * 0.5f);
	}
}

Player::Player(Vec2 position, float width, float height, float mass, float elasticity, float orientation) : Polygon(position, mass, elasticity), _width(width), _height(height)
{
	maxStepHeight = _height * 2 * maxStepFraction;
	footSlip = _width * 2 * footSlipFraction;

	float _maxX = +width * 0.5f;
	float _minX = -width * 0.5f;
	float _maxY = +height * 0.5f;
	float _minY = -height * 0.5f;

	_vertices.push_back(Vec2(_minX, _maxY).RotateBy(orientation));
	_vertices.push_back(Vec2(_maxX, _maxY).RotateBy(orientation));
	_vertices.push_back(Vec2(_maxX, _minY).RotateBy(orientation));
	_vertices.push_back(Vec2(_minX, _minY).RotateBy(orientation));

	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }

		_normals.push_back(Vec2(-(next.y - _vertices[i].y), next.x - _vertices[i].x).Normalise());
		_edgeCentres.push_back((_vertices[i] + next) * 0.5f);
	}
}

Player::Player(Vec2 position, float width, float height, float mass, float elasticity, float orientation, Vec2 velocity) : Player(position, width, height, mass, elasticity, orientation)
{
	_velocity = velocity;
}

Player::Player(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity) : Player(position, width, height, mass, elasticity)
{
	_velocity = velocity;
}

void Player::Update(float delta)
{
	PhysicsObject::Update(delta);
}

void Player::HandleInput(float delta)
{

	umbrella = false;

	if (!grounded)
	{
		umbrella = ApplicationHarness::IsKeyDown(Key::UpArrow);
	}

	float umbrellaInput = ApplicationHarness::GetInputAxis(Key::RightArrow, Key::LeftArrow);

	umbrellaAngle += umbrellaInput * delta * umbrellaAngleSpeed;
	umbrellaAngle = Lerp(umbrellaAngle, 0.0f, 2 * delta);

	umbrellaAngle = Clamp(umbrellaAngle, -40.0f, 40.0f);

	float horizontalInput = ApplicationHarness::GetInputAxis(Key::A, Key::D);

	if (!umbrella)
	{
		AddForce(Vec2(horizontalInput * MOVE_SPEED, 0));
	}
}

void Player::AttemptJump()
{
	if (grounded) AddImpulse({ 0, JUMP_HEIGHT });
}

void Player::Draw(LineRenderer* lines)
{
	lines->SetColour(Colour::MAGENTA);

	//Main Shape
	for (Vec2 vertice : _vertices)
	{
		lines->AddPointToLine(_position + vertice);
	}
	lines->FinishLineLoop();

	float minX = _vertices[0].x + _position.x;
	float maxX = _vertices[1].x + _position.x;
	float minY = _vertices[2].y + _position.y;
	float maxY = _vertices[1].y + _position.y;

	if(!debug) return;

	lines->SetColour(grounded ? Colour::GREEN : Colour::RED);

	//Ground Box
	lines->AddPointToLine(Vec2(minX + footSlip, minY));
	lines->AddPointToLine(Vec2(minX + footSlip, minY + maxStepHeight));
	lines->AddPointToLine(Vec2(maxX - footSlip, minY + maxStepHeight));
	lines->AddPointToLine(Vec2(maxX - footSlip, minY));

	lines->FinishLineLoop();

	lines->SetColour(Colour::BLUE);

	//Left Side
	lines->AddPointToLine(Vec2(minX, minY + maxStepHeight));
	lines->AddPointToLine(Vec2(minX, maxY));
	lines->AddPointToLine(Vec2(minX + headSlip, maxY));
	lines->AddPointToLine(Vec2(minX + headSlip, minY + maxStepHeight));

	lines->FinishLineLoop();

	//Right Side
	lines->AddPointToLine(Vec2(maxX, minY + maxStepHeight));
	lines->AddPointToLine(Vec2(maxX, maxY));
	lines->AddPointToLine(Vec2(maxX - headSlip, maxY));
	lines->AddPointToLine(Vec2(maxX - headSlip, minY + maxStepHeight));

	lines->FinishLineLoop();

	lines->SetColour(Colour::YELLOW);

	//Head Box
	lines->AddPointToLine(Vec2(minX + headSlip, maxY - maxStepHeight));
	lines->AddPointToLine(Vec2(minX + headSlip, maxY));
	lines->AddPointToLine(Vec2(maxX - headSlip, maxY));
	lines->AddPointToLine(Vec2(maxX - headSlip, maxY - maxStepHeight));

	lines->FinishLineLoop();

	//if (umbrella)
	//{
	//	lines->DrawCircleArc(_position + Vec2(0, 0.5f), 0.8f, PI / 4, 3 * PI / 4);
	//}
}
