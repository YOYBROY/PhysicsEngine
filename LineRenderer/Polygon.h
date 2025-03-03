#pragma once

#include <vector>

#include "PhysicsObject.h"

class Polygon : public PhysicsObject
{
protected:
	std::vector<Vec2> _vertices; //Stored in Object Space
	std::vector<Vec2> _normals; //Should be Updated each frame if rotation exists, need to be updated with World Space Vertice points
	std::vector<Vec2> _edgeCentres;


public:
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, float orientation);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, Vec2 velocity);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, float orientation, Vec2 velocity);
	Polygon(Vec2 position, float mass, float elasticity);

	void Draw(LineRenderer* lines) override;

	std::vector<Vec2> GetVertices() { return _vertices; }
	std::vector<Vec2> GetWorldSpaceVertices();
	std::vector<Vec2> GetNormals() { return _normals; }
	std::vector<Vec2> GetEdgeCentres() { return _edgeCentres; }
	ObjectType GetObjectType() override { return ObjectType::POLYGON; }
};