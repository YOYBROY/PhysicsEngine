#include "Player.h"

#include "TextStream.h"
#include "ApplicationHarness.h"
#include "Key.h"

Player::Player(Vec2 position, float width, float height, float mass, float elasticity) : Polygon(position, mass, elasticity), _width(width), _height(height)
{
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

void Player::Draw(LineRenderer* lines)
{
	//Polygon::Draw(lines);

	Colour playerColour = grounded ? Colour::GREEN : Colour::RED;

	for (Vec2 vertice : _vertices)
	{
		lines->AddPointToLine(_position + vertice, playerColour);
	}
	lines->FinishLineLoop();
	lines->DrawCircle(_position, 0.25f);
}

void Player::HandleInput()
{
	float horizontalInput = ApplicationHarness::GetInputAxis(Key::A, Key::D);

	AddForce(Vec2(horizontalInput * MOVE_SPEED, 0));
}

void Player::AttemptJump()
{
	if(grounded) AddImpulse({ 0, JUMP_HEIGHT });
}