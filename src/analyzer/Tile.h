#pragma once
class Tile
{
public:
	//const char8 TILE_RE = / ^ ([0 - 9][mps] | [1 - 7]z)$ / ;
	Tile(char type, int order);
	bool isValidTile(char type, int order);
};