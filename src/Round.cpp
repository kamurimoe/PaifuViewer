#include "Round.h"

Round::Round(const std::string& Yama)
{
    yama = Yama;
}

void Round::addActs(const std::string& act)
{
    if (!acts_text.empty())acts_text += ";";
    acts_text += act;
}
