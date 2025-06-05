#pragma once

class MajongGame
{
public:
	MajongGame();
	void start();
	void init(int playerNum, char* mode); //buff
	void play();
	void end();
};