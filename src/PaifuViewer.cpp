#include "Viewer.h"
#include "Reader.h"
#include "Stater.h"
#include "MajongGame.h"

// ui默认配置
constexpr int BASE_WIDTH = 800;
constexpr int BASE_HEIGHT = 600;
constexpr int BASE_FONT_SIZE = 13;
std::string BASE_TITLE = "牌谱复现";
std::string fontPath = RES_DIR"/fonts/simhei.ttf";
std::string charsetPath = RES_DIR"/fonts/charset.txt";

int main(int argc, char* argv[])
{
    Viewer viewer(BASE_WIDTH, BASE_HEIGHT, BASE_TITLE, BASE_FONT_SIZE);
    // 中文字体
    Viewer::loadCustomFont(fontPath, charsetPath);
    // layout
    Stater stater;
    // 文件导入
    Reader reader;
    MajongGame game;

    // 主循环
    while (!WindowShouldClose())
    {
        // 逻辑
        viewer.flashScale();
        // 导入牌谱
        if ((IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) || stater.input.btnInputPressed)
        {
            std::string fileName = reader.readFile();
            // 动态标题
            SetWindowTitle(TextFormat("%s | %s", BASE_TITLE.data(), GetFileName(fileName.data())));
            game.resetPaifu(fileName);
            std::vector<std::string> yamas;
            for (const auto& round : game.Rounds) {
                yamas.push_back(round.yama);
            }
            stater.initPlayYama(yamas);

        }

        BeginDrawing();
        // 绘制ui
        Viewer::whileDrawing();
        stater.setInput();
        Round* activeRound = game.getRound(stater.action.ActiveRoundIndex);
        stater.syncActiveRound();
        stater.setActionRoundsText(game.rounds_text, activeRound ? activeRound->acts_text : "");
        stater.setPlay();
        stater.setPlayYama();
        EndDrawing();
    }

    return 0;
}
