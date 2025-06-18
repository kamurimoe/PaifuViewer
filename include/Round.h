#pragma once

// #include "Tile.h"
#include <string>


class Round
{
public:
    explicit Round(const std::string& Yama);
    ~Round() = default;
    // Tiles yama;
    std::string acts_text;
    std::string yama;
    void addActs(const std::string& act);
};
