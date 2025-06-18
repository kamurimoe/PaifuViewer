#pragma once

#include "raylib.h"
// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifndef GUI_LAYOUT_ACTION_H
#define GUI_LAYOUT_ACTION_H

struct GuiLayoutActionState
{
    // Define controls variables
    Vector2 RoundsBoxBoundsOffset; // ScrollPanel: RoundsBox
    Vector2 ActsBoxBoundsOffset; // ScrollPanel: ActsBox
    // Rounds
    int ActiveRound;
    int ActiveRoundIndex;
    // Acts
    int ActiveAct;
    int ActiveActIndex;
    Rectangle RoundsTitleBounds;
    Rectangle RoundsBoxBounds;
    Rectangle ActsTitleBounds;
    Rectangle ActsBoxBounds;
};

GuiLayoutActionState InitGuiLayoutAction();

void GuiLayoutAction(GuiLayoutActionState* state, const char* rounds_text);

#endif // GUI_LAYOUT_ACTION_H

inline GuiLayoutActionState InitGuiLayoutAction()
{
    return GuiLayoutActionState{
        Vector2{0, 0},
        Vector2{0, 0},
        0,
        0,
        0,
        0,
        Rectangle{0, 48, 290, 24},
        Rectangle{0, 72, 290, 300},
        Rectangle{0, 355, 290, 24},
        Rectangle{0, 379, 290, 605},
    };
}


inline void GuiLayoutAction(GuiLayoutActionState* state, const char* rounds_text, const char* acts_text)
{
    // Const text
    const char* RoundsBoxText = "#41#回合";
    const char* ActsBoxText = "#42#行动";

    // RoundsBox
    GuiStatusBar(Rectangle{
                     state->RoundsTitleBounds.x, state->RoundsTitleBounds.y,
                     state->RoundsTitleBounds.width - state->RoundsBoxBoundsOffset.x,
                     state->RoundsTitleBounds.height - state->RoundsBoxBoundsOffset.y
                 }, RoundsBoxText);
    // 禁用取消选择
    int prevActiveRoundIndex = state->ActiveRoundIndex;
    GuiListView(Rectangle{
                    state->RoundsBoxBounds.x, state->RoundsBoxBounds.y,
                    state->RoundsBoxBounds.width - state->RoundsBoxBoundsOffset.x,
                    state->RoundsBoxBounds.height - state->RoundsBoxBoundsOffset.y
                }, rounds_text, &state->ActiveRound, &state->ActiveRoundIndex);
    if (state->ActiveRoundIndex == -1)state->ActiveRoundIndex = prevActiveRoundIndex;
    //ActionsBox
    GuiStatusBar(Rectangle{
                     state->ActsTitleBounds.x, state->ActsTitleBounds.y,
                     state->ActsTitleBounds.width - state->ActsBoxBoundsOffset.x,
                     state->ActsTitleBounds.height - state->ActsBoxBoundsOffset.y
                 }, ActsBoxText);
    // 禁用取消选择
    int prevActiveActionIndex = state->ActiveActIndex;
    GuiListView(Rectangle{ state->ActsBoxBounds.x, state->ActsBoxBounds.y, state->ActsBoxBounds.width - state->ActsBoxBoundsOffset.x, state->ActsBoxBounds.height - state->ActsBoxBoundsOffset.y }, acts_text, &state->ActiveAct, &state->ActiveActIndex);
    if (state->ActiveActIndex==-1) state->ActiveActIndex = prevActiveActionIndex;
}
