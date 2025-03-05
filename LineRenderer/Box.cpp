#include "Box.h"

#include "TextStream.h"

Box::Box(Vec2 position, float width, float height, float mass, float elasticity) : Polygon(position, mass, elasticity), _width(width), _height(height)
{
	float _maxX = + width * 0.5f;
	float _minX = - width * 0.5f;
	float _maxY = + height * 0.5f;
	float _minY = - height * 0.5f;

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

Box::Box(Vec2 position, float width, float height, float mass, float elasticity, float orientation) : Polygon(position, mass, elasticity), _width(width), _height(height)
{
	float _maxX = +width * 0.5f;
	float _minX = -width * 0.5f;
	float _maxY = +height * 0.5f;
	float _minY = -height * 0.5f;

	_vertices.push_back(Vec2(_minX, _maxY).RotateBy(orientation));
	_vertices.push_back(Vec2(_maxX, _maxY).RotateBy(orientation));
	_vertices.push_back(Vec2(_maxX, _minY).RotateBy(orientation));
	_vertices.push_back(Vec2(_minX, _minY).RotateBy(orientation));

	Vec2 next;
	for (int i = 0; i < _vertices.size(); i++)
	{
		if (i == _vertices.size() - 1) { next = _vertices[0]; }
		else { next = _vertices[i + 1]; }

		_normals.push_back(Vec2(-(next.y - _vertices[i].y), next.x - _vertices[i].x).Normalise());
		_edgeCentres.push_back((_vertices[i] + next) * 0.5f);
	}
}

Box::Box(Vec2 position, float width, float height, float mass, float elasticity, float orientation, Vec2 velocity) : Box(position, width, height, mass, elasticity, orientation)
{
	_velocity = velocity;
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
	if (!_visible) _colour = Colour::WHITE;
	//Polygon::Draw(lines);

	lines->SetColour(_colour);

	switch (_boxType)
	{
	case BoxType::U:
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::R:
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::D:
		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::L:
		lines->AddPointToLine(_vertices[3] + _position);
		lines->AddPointToLine(_vertices[0] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::UR:
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::UD:
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->FinishLineStrip();

		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::UL:
		lines->AddPointToLine(_vertices[3] + _position);
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::RD:
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::RL:
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->FinishLineStrip();

		lines->AddPointToLine(_vertices[3] + _position);
		lines->AddPointToLine(_vertices[0] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::DL:
		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->AddPointToLine(_vertices[0] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::URD:
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::RDL:
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->AddPointToLine(_vertices[0] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::DLU:
		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::LUR:
		lines->AddPointToLine(_vertices[3] + _position);
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->FinishLineStrip();
		break;
	case BoxType::URDL:
		lines->AddPointToLine(_vertices[0] + _position);
		lines->AddPointToLine(_vertices[1] + _position);
		lines->AddPointToLine(_vertices[2] + _position);
		lines->AddPointToLine(_vertices[3] + _position);
		lines->FinishLineLoop();
		break;
	default:
		break;
	}


	//TextStream output(lines, _position - Vec2(0.8, 0.45), 0.5f, Colour::SHREKGREEN);
	//output << "DVD ";
}