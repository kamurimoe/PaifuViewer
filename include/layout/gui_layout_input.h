#pragma once

#include "raylib.h"
// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifndef GUI_LAYOUT_INPUT_H
#define GUI_LAYOUT_INPUT_H

struct GuiLayoutInputState
{
    bool btnInputPressed;
    Rectangle btnInputBounds;
    // zoom相关
    bool dragMode;
    Rectangle panelBounds;
};

GuiLayoutInputState InitGuiLayoutInput();

void GuiLayoutInput(GuiLayoutInputState* state);

#endif // GUI_LAYOUT_INPUT_H


inline GuiLayoutInputState InitGuiLayoutInput()
{
    return GuiLayoutInputState{
        false,
        Rectangle{0, 0, 240+50, 40},
        false,
        Rectangle{static_cast<float>(GetScreenWidth()) - 168, 40, 168, static_cast<float>(GetScreenHeight()) - 40 - 24},
    };
}


inline void GuiLayoutInput(GuiLayoutInputState* state)
{
    // Const text
    const char* BtnInputText = "#217#牌谱";
    // BUTTON: BtnInput
    state->btnInputPressed = GuiButton(state->btnInputBounds, BtnInputText);
}
