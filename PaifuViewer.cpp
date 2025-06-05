#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_CUSTOM_RICONS
#include "raygui.h"
#include <vector>
#include <string>
#pragma execution_character_set("utf-8")

// 设计时的参考分辨率
#define BASE_WIDTH 800
#define BASE_HEIGHT 600

// 控件结构体
struct ScaledControl {
    Rectangle rect;      // 原始位置和大小（基于BASE_WIDTH和BASE_HEIGHT）
    int controlType;     // 控件类型
    const char* text;    // 控件文本
    bool value;           // 控件值（可选）
    const char* name;    // 控件名称（可选）
};

// 缩放后的矩形
Rectangle GetScaledRect(Rectangle originalRect, float scaleX, float scaleY) {
    return {
        originalRect.x * scaleX,
        originalRect.y * scaleY,
        originalRect.width * scaleX,
        originalRect.height * scaleY
    };
}

int main() {

    // 初始化窗口
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "可缩放窗口示例");
    SetWindowMinSize(BASE_WIDTH / 2, BASE_HEIGHT / 2);
    SetTargetFPS(60);
    //读取字体文件
    char guitests[] = "按钮被点击我开关复选框可缩放窗口示例";
    // 将字符串中的字符逐一转换成Unicode码点，得到码点表
    int codepointsCount;
    int* codepoints = LoadCodepoints(guitests, &codepointsCount);
    // 读取仅含码点表中各字符的字体
    Font font = LoadFontEx("res/fonts/FZXIANGSU12.TTF", 64, codepoints, codepointsCount);
    // 释放码点表
    UnloadCodepoints(codepoints);

    //设置GUI控件的字体
    GuiSetFont(font);

    // 创建控件列表 - 使用最新的RayGUI控件类型
    std::vector<ScaledControl> controls = {
        {{50, 50, 200, 30}, BUTTON, "点击我", false, "button1"},
        {{50, 100, 200, 30}, TOGGLE, "开关", false, "toggle1"},
        {{50, 150, 200, 30}, CHECKBOX, "复选框", false, "checkbox1"},
    };

    // 主循环
    while (!WindowShouldClose()) {
        // 计算当前窗口相对于基础分辨率的缩放比例
        float scaleX = (float)GetScreenWidth() / BASE_WIDTH;
        float scaleY = (float)GetScreenHeight() / BASE_HEIGHT;
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20*std::min(scaleX,scaleY));
        // 开始绘制
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // 绘制所有控件
        for (auto& control : controls) {
            Rectangle scaledRect = GetScaledRect(control.rect, scaleX, scaleY);

            // 根据控件类型绘制
            switch (control.controlType) {
            case BUTTON:
                if (GuiButton(scaledRect, control.text)) {
                    // 按钮点击事件
                }
                break;

            case TOGGLE:
                control.value = GuiToggle(scaledRect, control.text, &control.value);
                break;

            case CHECKBOX:
                control.value = GuiCheckBox(scaledRect, control.text, &control.value);
                break;

            default:
                break;
            }
        }
        EndDrawing();
    }

    // 清理
    UnloadFont(font);
    CloseWindow();
    return 0;
}