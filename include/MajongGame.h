#pragma once
#include "Round.h"

#include <nlohmann/json.hpp>
using njson = nlohmann::json;

class MajongGame
{
public:
	MajongGame();
	njson paifu;
	njson actions_ptr;
	std::vector<std::string> seats;
	std::string rounds_text;
	std::vector<Round> Rounds;
	void start();
	void init(int playerNum, char* mode); //buff
	void play();
	void end();
	Round* getRound(int i);
	void unloadPaifu() const;
	void resetPaifu(const std::string &fileName);
private:
	void parseAction(const njson& a);
	void parsePaifu();
};