#pragma once

#include <string>


class Reader
{
public:
    Reader() = default;
    ~Reader() = default;
    bool showLoadFileDialog = false;
    bool gotPaifu = false;

    std::string readFile();
};
