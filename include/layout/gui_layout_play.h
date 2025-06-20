#pragma once

#include "raylib.h"
#include <vector>
#include <string>

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifndef GUI_LAYOUT_PLAY_H
#define GUI_LAYOUT_PLAY_H

struct TileInfo
{
    Vector2 pos;

    std::string name;
};

struct GuiLayoutPlayState
{
    Rectangle YamaBoxScrollView;
    Vector2 YamaBoxScrollOffset;
    // Define rectangles
    Rectangle PlayBoxBounds;
    Rectangle RinShanBoxBounds;
    Rectangle YamaBoxBounds;
    Rectangle YamaBoxContent;
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
    //
    int ActiveRound;
    std::vector<std::vector<TileInfo>> YamaTilesInfo;
};

inline std::vector<std::vector<Texture2D>> tilesTextures; // Tiles Texture2D

GuiLayoutPlayState InitGuiLayoutPlay();
void GuiLayoutPlay(GuiLayoutPlayState* state);
void InitGuiLayoutPlayYama(GuiLayoutPlayState* state, const std::string& yama);
void GuiLayoutPlayYama(const GuiLayoutPlayState* state, const std::string& yama);
#endif // GUI_LAYOUT_PLAY_H


inline GuiLayoutPlayState InitGuiLayoutPlay()
{
    GuiLayoutPlayState state = {

        Rectangle{0, 0, 0, 0},
        Vector2{0, 0},
        Rectangle{50 + 248, 0, 1672 - 50, 984},
        Rectangle{50 + 256, 32, 30 + 624, 176},
        Rectangle{50 + 256, 216, 30 + 624, 432},
        Rectangle{50 + 256, 216, 30 + 624 - 16, 432 - 24},
        Rectangle{50 + 256, 656, 30 + 624, 320},
        Rectangle{100 + 1192, 352, 296, 296},
        Rectangle{100 + 1184, 664, 312, 208},
        Rectangle{100 + 1504, 344, 208, 312},
        Rectangle{100 + 1184, 128, 312, 208},
        Rectangle{100 + 968, 344, 208, 312},
        Rectangle{100 + 968, 896, 747, 52},
        Rectangle{100 + 1736, 128, 52, 747},
        Rectangle{100 + 968, 56, 747, 52},
        Rectangle{100 + 896, 128, 52, 747}
    };

    // Tiles Texture2D
    tilesTextures.resize(4);
    const std::string dir = RES_DIR "/tiles/";
    for (int i = 0; i < 4; i++)
    {
        tilesTextures[i].resize(10);
        for (int j = 0; j < 10; j++)
        {
            if (i == 3 && j == 8) break;
            if (i == 3 && j == 0)
            {
                tilesTextures[3][0] = LoadTexture((dir + "Front.png").data());
            }
            else
            {
                std::string path = dir + std::to_string(i) + std::to_string(j) + ".png";
                tilesTextures[i][j] = LoadTexture(path.data());
            }
        }
    }

    return state;
}

// 牌山
inline void Tile2Order(const std::string& tile, int* order)
{
    order[1] = tile[0] - '0';
    order[0] = tile[1] == 'm' ? 0 : tile[1] == 'p' ? 1 : tile[1] == 's' ? 2 : tile[1] == 'z' ? 3 : -1;
}

inline void InitGuiLayoutPlayYama(GuiLayoutPlayState* state, const std::vector<std::string>& yamas)
{
    // BoxContentHeight
    state->YamaBoxContent.height = static_cast<int>(yamas[0].size() / 24 + 1) * 65; // 每个牌山的高度为65px
    // TilesPosition
    constexpr int init_hand_num = 3 * 13 + 1; // 3麻初始手牌数
    constexpr int hand_row_num = init_hand_num / 12;
    constexpr int offset_by_hand = init_hand_num % 12;
    state->YamaTilesInfo.resize(yamas.size());
    for (int i = 0; i < yamas.size(); i++)
    {
        const int yama_size = yamas[i].size();
        state->YamaTilesInfo[i].resize(yama_size / 2);
        for (int j = 0; j < yama_size; j += 2)
        {
            const std::string tile = yamas[i].substr(j, 2);
            const int index = j / 2;
            // const int index_t = index + (index > init_hand_num - 1 ? 12 - offset_by_hand : 0);
            const int row = (index + (index > init_hand_num - 1 ? 13 - offset_by_hand : 0)) / 12;
            const int col = (index + (index > init_hand_num - 1 ? 13 - offset_by_hand : 0)) % 12;
            const int span = row > hand_row_num ? col / 3 * 8 : col / 4 * 10;
            auto& [pos, name] = state->YamaTilesInfo[i][index];
            pos.x = 311 + col * 51 + span;
            pos.y = 240 + row * 65;
            name = tile;
        }
    }
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
    GuiScrollPanel(state->YamaBoxBounds, YamaBoxText,
                   state->YamaBoxContent,
                   &state->YamaBoxScrollOffset,
                   &state->YamaBoxScrollView);

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

inline void GuiLayoutPlayYama(const GuiLayoutPlayState* state)
{
    if (state->YamaTilesInfo.empty()) return;
    BeginScissorMode(state->YamaBoxScrollView.x, state->YamaBoxScrollView.y,
                     state->YamaBoxScrollView.width, state->YamaBoxScrollView.height);
    GuiLock();
    const auto temp_order = new int[2];

    const std::vector<TileInfo> yamaInfo = state->YamaTilesInfo[state->ActiveRound];
    for (int i = 0; i < yamaInfo.size(); i++)
    {
        Tile2Order(yamaInfo[i].name, temp_order);
        const auto [x, y] = yamaInfo[i].pos;
        const Vector2 cell = {x, y + state->YamaBoxScrollOffset.y};
        DrawTextureEx(tilesTextures[3][0], cell, 0.0, 0.080, GRAY);
        DrawTextureEx(tilesTextures[temp_order[0]][temp_order[1]], cell, 0.0, 0.080, WHITE);
    }
    GuiUnlock();
    EndScissorMode();
}

inline void GuiLayoutPlayHands(GuiLayoutPlayState* state, const std::string& yama)
{
}
