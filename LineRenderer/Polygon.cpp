#include "Polygon.h"
#include <iostream>

Polygon::Polygon(Vec2 position, std::vector<Vec2> verts, float mass, float elasticity) : PhysicsObject(position, mass, elasticity)
{
	_startingVerts = verts;
}

Polygon::Polygon(Vec2 position, std::vector<Vec2> verts, float mass, float elasticity, Vec2 velocity) : Polygon(position, verts, mass, elasticity)
{
	_velocity = velocity;
}

//Base
Polygon::Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity) : PhysicsObject(position, mass, elasticity)
{
	Vec2 offsetVector(0, padding);
	for (int i = 0; i < vertCount; i++)
	{
		_startingVerts.push_back(offsetVector);
		offsetVector.RotateBy(-2 * PI / vertCount);
	}
}
//Orientation
Polygon::Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, float orientation) : PhysicsObject(position, mass, elasticity)
{
	_orientation = orientation;
	Vec2 offsetVector(0, padding);
	for (int i = 0; i < vertCount; i++)
	{
		_startingVerts.push_back(offsetVector);
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

void Polygon::Update(float delta)
{
	_vertices = _startingVerts;
	for (Vec2& vertex : _vertices)
	{
		vertex.RotateBy(_orientation);
	}

	//recalculateNormals

	_normals.clear();
	_edgeCentres.clear();
	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }

		_normals.push_back(Vec2(-(next.y - _vertices[i].y), next.x - _vertices[i].x).Normalise());
		_edgeCentres.push_back((_vertices[i] + next) * 0.5f);
	}
	PhysicsObject::Update(delta);
}

void Polygon::Draw(LineRenderer* lines)
{
	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }

		lines->DrawLineSegment(_position + _vertices[i], _position + next, _colour);
		//lines->DrawText(std::to_string(i), worldVerts[i], 0.1f);
		lines->DrawCross(_position, 0.03f);

		//Draw normals debug
		lines->DrawLineWithArrow((_position + _edgeCentres[i]), (_position + _edgeCentres[i] + _normals[i]));
	}
	_colour = Colour::SHREKGREEN;
}

void Polygon::SetVertices(std::vector<Vec2> newVerts)
{
	_startingVerts = newVerts;
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
