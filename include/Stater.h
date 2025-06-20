#pragma once

#include "layout/gui_layout_input.h"
#include "layout/gui_layout_action.h"
#include "layout/gui_layout_play.h"
#include <string>


class Stater
{
public:
    Stater() = default;
    ~Stater() = default;
    GuiLayoutInputState input = InitGuiLayoutInput();
    GuiLayoutActionState action = InitGuiLayoutAction();
    GuiLayoutPlayState play = InitGuiLayoutPlay();
    void setInput();
    void setActionRoundsText(const std::string& rounds_text, const std::string& acts_text);
    void setPlay();
    void initPlayYama(const std::vector<std::string>& yamas);
    void setPlayYama() const;
    void syncActiveRound();
};
