#include "Circle.h"

Circle::Circle(Vec2 position, float radius, float mass, float elasticity) : PhysicsObject(position, mass, elasticity), _radius(radius)
{
}

Circle::Circle(Vec2 position, float radius, float mass, float elasticity, Vec2 velocity) : PhysicsObject(position, mass, elasticity, velocity), _radius(radius)
{
}

void Circle::Draw(LineRenderer* lines)
{
	lines->DrawCircle(_position, _radius, _colour);
	lines->DrawCross(_position, 0.1f);
}