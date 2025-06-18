#pragma once

// #include "Tile.h"
#include <string>
#include <vector>

struct ActionPlayerArea
{
    std::string HandTiles;
    std::string DealtTile;
    std::string DiscardedTile;
    std::string KawaTiles;
    std::string OpenTiles;
    std::string BeiTiles;
};

struct RoundPanel
{
    int actingPlayerSeat;;
    int OyaSeat;
};

class Round
{
public:
    explicit Round(const std::string& Yama);
    ~Round() = default;
    // Tiles yama;
    std::string acts_text = "配牌";
    std::string rinshan;
    std::string yama;
    RoundPanel panel;
    std::vector<ActionPlayerArea> playerAreas;
    void addActs(const std::string& act);
};
