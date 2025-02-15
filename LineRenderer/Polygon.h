#pragma once

#include <vector>

#include "PhysicsObject.h"

class Polygon : public PhysicsObject
{
protected:
	std::vector<Vec2> _vertices;
	std::vector<Vec2> _normals;
	std::vector<Vec2> _edgeCentres;

	ObjectType _objectType = POLYGON;

public:
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, Vec2 velocity);

	void Draw(LineRenderer* lines) override;

	std::vector<Vec2> GetVertices() { return _vertices; }
	std::vector<Vec2> GetNormals() { return _normals; }
	std::vector<Vec2> GetEdgeCentres() { return _edgeCentres; }

	ObjectType GetObjectType() override { return _objectType; }
};