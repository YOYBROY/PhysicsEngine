#pragma once

#include <vector>

#include "PhysicsObject.h"
#include "Polygon.h"

class Box : public Polygon
{
protected:
	float _width;
	float _height;
public:
	Box(Vec2 position, float width, float height, float mass, float elasticity);
	Box(Vec2 position, float width, float height, float mass, float elasticity, Vec2 velocity);

	void Update(float delta) override;
	void Draw(LineRenderer* lines) override;

	float GetWidth() { return _width; }
	void SetWidth(float width) { _width = width; }

	float GetHeight() { return _height; }
	void GetHeight(float height) { _height = height; }

	std::vector<Vec2> GetVertices() { return _vertices; }
	std::vector<Vec2> GetWorldSpaceVertices();
	//std::vector<Vec2> GetNormals() { return _normals; }
	std::vector<Vec2> GetEdgeCentres() { return _edgeCentres; }

	ObjectType GetObjectType() override { return _objectType; }
};