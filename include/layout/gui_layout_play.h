#pragma once

#include "raylib.h"
#include <vector>
#include <string>

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifndef GUI_LAYOUT_PLAY_H
#define GUI_LAYOUT_PLAY_H

struct GuiLayoutPlayState
{
    Rectangle YamaBoxScrollView;
    Vector2 YamaBoxScrollOffset;
    Vector2 YamaBoxBoundsOffset; // ScrollPanel: YamaBox

    // Define rectangles
    Rectangle PlayBoxBounds;
    Rectangle RinShanBoxBounds;
    Rectangle YamaBoxBounds;
    Rectangle RoundResBoxBounds;
    Rectangle RoundPannelBounds;
    Rectangle SelfKawaBounds;
    Rectangle ShimoKawaBounds;
    Rectangle ToiKawaBounds;
    Rectangle KamiKawaBounds;
    Rectangle SelfHandBounds;
    Rectangle ShimoHandBounds;
    Rectangle ToiHandBounds;
    Rectangle KamiHandBounds;
    std::vector<std::vector<Texture2D>> tilesTextures; // Tiles Texture2D
};

GuiLayoutPlayState InitGuiLayoutPlay();

void GuiLayoutPlay(GuiLayoutPlayState* state);

void GuiLayoutPlayYama(const GuiLayoutPlayState* state, const std::string& yama);
#endif // GUI_LAYOUT_PLAY_H


inline GuiLayoutPlayState InitGuiLayoutPlay()
{
    GuiLayoutPlayState state = {

        Rectangle{0, 0, 0, 0},
        Vector2{0, 0},
        Vector2{0, 0},
        Rectangle{50 + 248, 0, 1672 - 50, 984},
        Rectangle{50 + 256, 32, 30 + 624, 176},
        Rectangle{50 + 256, 216, 30 + 624, 432},
        Rectangle{50 + 256, 656, 30 + 624, 320},
        Rectangle{100 + 1192, 352, 296, 296},
        Rectangle{100 + 1184, 664, 312, 208},
        Rectangle{100 + 1504, 344, 208, 312},
        Rectangle{100 + 1184, 128, 312, 208},
        Rectangle{100 + 968, 344, 208, 312},
        Rectangle{100 + 968, 896, 747, 52},
        Rectangle{100 + 1736, 128, 52, 747},
        Rectangle{100 + 968, 56, 747, 52},
        Rectangle{100 + 896, 128, 52, 747},
    };
    // Tiles Texture2D
    state.tilesTextures.resize(4);
    std::string dir = RES_DIR "/tiles/";
    for (int i = 0; i < 4; i++)
    {
        state.tilesTextures[i].resize(10);
        for (int j = 0; j < 10; j++)
        {
            if (i == 3 && j == 8) break;
            if (i == 3 && j == 0)
            {
                state.tilesTextures[3][0] = LoadTexture((dir + "Front.png").data());
            }
            else
            {
                std::string path = dir + std::to_string(i) + std::to_string(j) + ".png";
                state.tilesTextures[i][j] = LoadTexture(path.data());
            }
        }
    }
    return state;
}


inline void GuiLayoutPlay(GuiLayoutPlayState* state)
{
    // Const text
    const char* PlayBoxText = "#169#复现";
    const char* RinShanBoxText = "#157#岭上";
    const char* YamaBoxText = "#101#牌山";
    const char* RoundResBoxText = "#191#整场结果";

    GuiPanel(state->PlayBoxBounds, PlayBoxText);
    GuiPanel(state->RinShanBoxBounds, RinShanBoxText);
    GuiScrollPanel(
        Rectangle{
            state->YamaBoxBounds.x, state->YamaBoxBounds.y, state->YamaBoxBounds.width - state->YamaBoxBoundsOffset.x,
            state->YamaBoxBounds.height - state->YamaBoxBoundsOffset.y
        }, YamaBoxText, state->YamaBoxBounds, &state->YamaBoxScrollOffset, &state->YamaBoxScrollView);
    GuiPanel(state->RoundResBoxBounds, RoundResBoxText);
    GuiPanel(state->RoundPannelBounds, nullptr);
    GuiPanel(state->SelfKawaBounds, nullptr);
    GuiPanel(state->ShimoKawaBounds, nullptr);
    GuiPanel(state->ToiKawaBounds, nullptr);
    GuiPanel(state->KamiKawaBounds, nullptr);
    GuiPanel(state->SelfHandBounds, nullptr);
    GuiPanel(state->ShimoHandBounds, nullptr);
    GuiPanel(state->ToiHandBounds, nullptr);
    GuiPanel(state->KamiHandBounds, nullptr);
}

// 牌山
inline void Tile2Order(const std::string& tile, int* order)
{
    order[1] = tile[0] - '0';
    order[0] = tile[1] == 'm' ? 0 : tile[1] == 'p' ? 1 : tile[1] == 's' ? 2 : tile[1] == 'z' ? 3 : -1;
}

inline void GuiLayoutPlayYama(const GuiLayoutPlayState* state, const std::string& yama)
{
    constexpr int init_hand_num = 3 * 13 + 1; // 3麻初始手牌数
    constexpr int hand_row_num = init_hand_num / 12;
    constexpr int offset_by_hand = init_hand_num % 12;
    for (int i = 0; i < yama.size(); i += 2)
    {
        std::string tile = yama.substr(i, 2);
        int order[2] = {0, 0};
        Tile2Order(tile, order);
        const int index = i / 2;
        const int index_t = (index + (index > init_hand_num - 1 ? 12 - offset_by_hand : 0));
        const int row = index_t / 12;
        const int col = index_t % 12;
        const int span = row > hand_row_num ? static_cast<int>(col / 3) * 5 : static_cast<int>(col / 4) * 5;

        const float x = 261 + 50 + col * 52 + span;
        const float y = 240 + row * 65;
        const Vector2 cell = {x, y};
        DrawTextureEx(state->tilesTextures[3][0], cell, 0.0, 0.080, GRAY);
        DrawTextureEx(state->tilesTextures[order[0]][order[1]], cell, 0.0, 0.080, WHITE);
    }
}

inline void GuiLayoutPlayHands(GuiLayoutPlayState* state, const std::string& yama)
{
}
