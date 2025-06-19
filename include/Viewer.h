#pragma once

#include <iostream>
#include <string>

class Viewer
{
public:
    Viewer(int width, int height, const std::string& title, int fontSize);
    ~Viewer();

    void flashScale();

    static void whileDrawing();

    static void loadCustomFont(const std::string& fontPath, const std::string& charsetPath);

private:
    float scaleX = 1.0;
    float scaleY = 1.0;
    int baseWidth;
    int baseHeight;
    int baseFontSize;
};
