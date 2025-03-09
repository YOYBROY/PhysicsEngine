#include "Polygon.h"
#include <iostream>

//Base
Polygon::Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity) : PhysicsObject(position, mass, elasticity)
{
	Vec2 offsetVector(0, padding);
	for (int i = 0; i < vertCount; i++)
	{
		_vertices.push_back(offsetVector);
		offsetVector.RotateBy(-2 * PI / vertCount);
	}

	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }

		_normals.push_back(Vec2(-(next.y - _vertices[i].y), next.x - _vertices[i].x).Normalise());
		_edgeCentres.push_back((_vertices[i] + next) * 0.5f);
	}
}
//Orientation
Polygon::Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, float orientation) : PhysicsObject(position, mass, elasticity)
{
	Vec2 offsetVector(0, padding);
	offsetVector.RotateBy(DegToRad(orientation));
	for (int i = 0; i < vertCount; i++)
	{
		_vertices.push_back(offsetVector);
		offsetVector.RotateBy(-2 * PI / vertCount);
	}

	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }

		_normals.push_back(Vec2(-(next.y - _vertices[i].y), next.x - _vertices[i].x).Normalise());
		_edgeCentres.push_back((_vertices[i] + next) * 0.5f);
	}
}

//with Velocity
Polygon::Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, Vec2 velocity) : Polygon(position, vertCount, padding, mass, elasticity)
{
	_velocity = velocity;
}
//Orientation + Velocity
Polygon::Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, float orientation, Vec2 velocity) : Polygon(position, vertCount, padding, mass, elasticity, orientation)
{
	_velocity = velocity;
}

Polygon::Polygon(Vec2 position, float mass, float elasticity) : PhysicsObject(position, mass, elasticity)
{
}

void Polygon::Draw(LineRenderer* lines)
{
	std::vector<Vec2> worldVerts = GetWorldSpaceVertices();
	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }
		lines->DrawLineSegment(_position + _vertices[i], _position + next, _colour);
		lines->DrawText(std::to_string(i), worldVerts[i], 0.1f);

		//Draw normals debug
		//lines->DrawLineWithArrow((_position + _edgeCentres[i]), (_position + _edgeCentres[i] + _normals[i]));
	}
	_colour = Colour::SHREKGREEN;
}

std::vector<Vec2> Polygon::GetWorldSpaceVertices()
{
	std::vector<Vec2> worldSpaceVertices;
	for (Vec2 vertex : _vertices)
	{
		worldSpaceVertices.push_back(_position + vertex);
	}
	return worldSpaceVertices;
}
