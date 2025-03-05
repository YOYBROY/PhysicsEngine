#pragma once

#include <iostream>
#include <string>

enum class TileType
{
	EMPTY = 0xFFFFFF,
	PLATFORM = 0x000000,
	PLAYERSTART = 0xFF0000 //Endianess is backward to most art tools, it goes (Blue, Green, Red)

};

class Grid
{
	TileType* data = nullptr;
	int width = 0;
	int height = 0;

public:
	Grid() = default;
	void LoadFromImage(std::string fileName);

	TileType& At(int xCoord, int yCoord);
	TileType& AtWrap(int xCoord, int yCoord);
	TileType& AtClamp(int xCoord, int yCoord);

	~Grid();
	Grid(Grid& other) = delete;
	Grid& operator=(Grid& other) = delete;

	int GetHeight() const { return height; }
	int GetWidth() const { return width; }
};