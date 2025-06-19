#include "Viewer.h"
#include "raylib.h"
#include "raygui.h"
#include "style/YuzuStyle.h"
#include <fstream>

Rectangle ScaledTransRect(const Rectangle oRect, const float scaleX, const float scaleY)
{
    // 计算缩放及变换坐标
    return {
        (oRect.x - oRect.width / 2) * scaleX,
        (oRect.y - oRect.height / 2) * scaleY,
        oRect.width * scaleX,
        oRect.height * scaleY
    };
}

Viewer::Viewer(const int width, const int height, const std::string& title, const int fontSize)
{
    // 初始化窗口
    baseWidth = width;
    baseHeight = height;
    baseFontSize = fontSize;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, title.data());
    SetWindowMinSize(baseWidth / 2, baseHeight / 2);
    SetTargetFPS(30);
    GuiLoadStyleYuzuStyle();
}

Viewer::~Viewer()
{
    UnloadFont(GuiGetFont());
}

void Viewer::whileDrawing()
{
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
}

void Viewer::loadCustomFont(const std::string& fontPath, const std::string& charsetPath)
{
    int codepointsCount;
    std::ifstream file(charsetPath, std::ios::binary);
    const auto text = std::string(std::istreambuf_iterator(file),
                                   std::istreambuf_iterator<char>());
    //char* text = LoadFileText(charsetPath.data());
    int* codepoints = LoadCodepoints(text.data(), &codepointsCount);
    const Font font = LoadFontEx(fontPath.data(), 64, codepoints, codepointsCount);
    UnloadCodepoints(codepoints);
    GuiSetFont(font);
}

void Viewer::flashScale()
{
    scaleX = static_cast<float>(GetScreenWidth()) / static_cast<float>(baseWidth);
    scaleY = static_cast<float>(GetScreenHeight()) / static_cast<float>(baseHeight);
    GuiSetStyle(DEFAULT, TEXT_SIZE, baseFontSize * static_cast<int>(std::min(scaleX, scaleY)));
}
