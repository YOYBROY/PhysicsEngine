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

void Box::Draw(LineRenderer* lines)
{
	Vec2 point1 = Vec2(_minX, _maxY) + _position;
	Vec2 point2 = Vec2(_maxX, _maxY) + _position;
	Vec2 point3 = Vec2(_maxX, _minY) + _position;
	Vec2 point4 = Vec2(_minX, _minY) + _position;

	//Clockwise from top left
	lines->DrawLineSegment(point1, point2);
	lines->DrawLineSegment(point2, point3);
	lines->DrawLineSegment(point3, point4);
	lines->DrawLineSegment(point4, point1);
}