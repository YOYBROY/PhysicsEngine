#pragma once

#include <vector>

#include "PhysicsObject.h"

class Polygon : public PhysicsObject
{
protected:
	std::vector<Vec2> _startingVerts; //the starting vertices of the polygon
	std::vector<Vec2> _vertices; //Stored in Object Space, updated each frame to show the rotation
	std::vector<Vec2> _normals; //Should be Updated each frame if rotation exists, need to be updated with World Space Vertice points
	std::vector<Vec2> _edgeCentres;

public:
	Polygon(Vec2 position, std::vector<Vec2> verts, float mass, float elasticity);
	Polygon(Vec2 position, std::vector<Vec2> verts, float mass, float elasticity, Vec2 velocity);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, float orientation);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, Vec2 velocity);
	Polygon(Vec2 position, int vertCount, float padding, float mass, float elasticity, float orientation, Vec2 velocity);
	Polygon(Vec2 position, float mass, float elasticity);

	void Draw(LineRenderer* lines) override;
	void Update(float delta) override;

	std::vector<Vec2> GetVertices() { return _vertices; }
	void SetVertices(std::vector<Vec2> newVerts);
	std::vector<Vec2> GetWorldSpaceVertices();
	std::vector<Vec2> GetNormals() { return _normals; }
	std::vector<Vec2> GetEdgeCentres() { return _edgeCentres; }
	ObjectType GetObjectType() override { return ObjectType::POLYGON; }
};