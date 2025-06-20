#include "Round.h"

Round::Round(const std::string& Yama)
{
    yama = Yama;
}

void Round::addActs(const std::string& act)
{
    acts_text += (";"+ act);
}
