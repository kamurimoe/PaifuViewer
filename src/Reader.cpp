#include "Reader.h"
#include "layout/gui_file_dialogs.h"


std::string Reader::readFile() {
    char fileName[256] = {0};
    // 拖入或选择文件
    //#if defined(CUSTOM_MODAL_DIALOGS)
    //        int result = GuiFileDialog(DIALOG_MESSAGE, "#5#Load raygui paifu file", inFileName, "Ok", "Just drag and drop your .rgl paifu file!");
    //#else
    GuiFileDialog(DIALOG_OPEN_FILE, "Load paifu json file", fileName, "*.json",
                               "paifu json files (*.json)");
    //#endif
    gotPaifu = true;
    return fileName;
}
