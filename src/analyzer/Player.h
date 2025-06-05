#pragma once
#include "Tile.h"
class Player
{
public:
	Player(int seat, Tile* hand);
	void deal(Tile* tile);
	void discard(Tile* tile);
	void kita();
	void open(Tile* tile, Tile* handTiles);
	void kan(Tile* tile);
	void syanten();
	bool isKokushiTenpai();
};

