#include "Box.h"

Box::Box(Vec2 position, float width, float height, float mass, float elasticity) : Polygon(position, mass, elasticity), _width(width), _height(height)
{
	float _maxX = position.x + width * 0.5f;
	float _minX = position.x - width * 0.5f;
	float _maxY = position.y + height * 0.5f;
	float _minY = position.y - height * 0.5f;

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

Box::Box(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity) : Box(position, width, height, mass, elasticity)
{
	_velocity = velocity;
}

void Box::Update(float delta)
{
	PhysicsObject::Update(delta);
}

void Box::Draw(LineRenderer* lines)
{
	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }
		lines->DrawLineSegment(_position + _vertices[i], _position + next, _colour);

		//Draw normals debug
		lines->DrawLineWithArrow((_position + _edgeCentres[i]), (_position + _edgeCentres[i] + _normals[i]));
	}
	_colour = Colour::GREEN;
}

std::vector<Vec2> Box::GetWorldSpaceVertices()
{
	std::vector<Vec2> worldSpaceVertices;
	for (Vec2 vertex : _vertices)
	{
		worldSpaceVertices.push_back(_position + vertex);
	}
	return worldSpaceVertices;
}