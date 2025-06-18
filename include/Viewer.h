#pragma once

#include <iostream>
#include <string>

class Viewer
{
public:
    Viewer(float width, float height, const std::string& title, int fontSize);
    ~Viewer();

    void flashScale();

    static void inDrawing();

    static void loadCustomFont(const std::string& fontPath, const std::string& charsetPath);

private:
    float scaleX = 1.0;
    float scaleY = 1.0;
    float baseWidth;
    float baseHeight;
    float baseFontSize;
};
