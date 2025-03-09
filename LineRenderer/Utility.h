#pragma once
#include "Vec2.h"
#include <vector>

Vec2 RemapFromFloatToVec2(float value, float aMin, float aMax, Vec2 bMin, Vec2 bMax);
Vec2 GetMidpoint(std::vector<Vec2> verts);
void FixWindingOrder(std::vector<Vec2>& verts);
void FixWindingOrder2(std::vector<Vec2>& verts);