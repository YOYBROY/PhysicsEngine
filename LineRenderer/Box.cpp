#include "Box.h"

Box::Box(Vec2 position, float width, float height, float mass, float elasticity) : PhysicsObject(position, mass, elasticity), _width(width), _height(height)
{
	_maxX = position.x + width * 0.5f;
	_minX = position.x - width * 0.5f;
	_maxY = position.y + height * 0.5f;
	_minY = position.y - height * 0.5f;
}

Box::Box(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity) : PhysicsObject(position, mass, elasticity, velocity), _width(width), _height(height)
{
	_maxX = position.x + width * 0.5f;
	_minX = position.x - width * 0.5f;
	_maxY = position.y + height * 0.5f;
	_minY = position.y - height * 0.5f;
}



void Box::Update(float delta)
{
	PhysicsObject::Update(delta);
	_maxX = _position.x + _width * 0.5f;
	_minX = _position.x - _width * 0.5f;
	_maxY = _position.y + _height * 0.5f;
	_minY = _position.y - _height * 0.5f;
}

void Box::Draw(LineRenderer* lines)
{
	if (_collisionAccumulation > 0)
	{
		_colour = Colour::RED;
	}
	else
	{
		_colour = Colour::GREEN;
	}

	Vec2 point1 = Vec2(_minX, _maxY);
	Vec2 point2 = Vec2(_maxX, _maxY);
	Vec2 point3 = Vec2(_maxX, _minY);
	Vec2 point4 = Vec2(_minX, _minY);

	//Clockwise from top left
	lines->DrawLineSegment(point1, point2, _colour);
	lines->DrawLineSegment(point2, point3, _colour);
	lines->DrawLineSegment(point3, point4, _colour);
	lines->DrawLineSegment(point4, point1, _colour);

	_collisionAccumulation = 0;
}