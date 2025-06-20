#include "Stater.h"


void Stater::setInput()
{
    GuiLayoutInput(&input);
}

void Stater::setActionRoundsText(const std::string& rounds_text, const std::string& acts_text)
{
    GuiLayoutAction(&action, rounds_text.data(), acts_text.data());
}

void Stater::setPlay()
{
    GuiLayoutPlay(&play);
}

void Stater::initPlayYama(const std::vector<std::string>& yamas)
{
    InitGuiLayoutPlayYama(&play, yamas);
}

void Stater::setPlayYama() const
{
    GuiLayoutPlayYama(&play);
}

void Stater::syncActiveRound()
{
    play.ActiveRound = action.ActiveRoundIndex;
}
