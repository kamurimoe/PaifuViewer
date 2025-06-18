#include "MajongGame.h"
#include <fstream>
#include <format>
#include <iostream>

const std::string seat_order[] = {"东", "南", "西", "北"};

MajongGame::MajongGame()
{
}

void MajongGame::start()
{
}

void MajongGame::init(int playerNum, char* mode)
{
}

void MajongGame::play()
{
}

void MajongGame::end()
{
}

Round* MajongGame::getRound(const int i)
{
    if (i >= Rounds.size())return nullptr;
    return &Rounds[i];
}

void MajongGame::parseAction(const njson& a)
{
    //std::string time = a["passed"]+"ms";
    const std::string actionName = a["result"]["name"].get<std::string>();
    njson actionData = a["result"]["data"];
    if (actionName == ".lq.RecordNewRound")
    {
        const int chang = actionData["chang"].get<int>();
        const int ju = actionData["ju"].get<int>();
        const int ben = actionData["ben"].get<int>();
        if (rounds_text.size() != 0)rounds_text += ";";
        rounds_text += std::format("{}{}局{}本场", seat_order[chang], ju, ben);
        Rounds.push_back(Round(actionData["paishan"].get<std::string>()));
    }
    else
    {
        Round* activeRound = getRound(Rounds.size() - 1);
        if (actionName == ".lq.RecordDealTile")
        {
        }
        else if (actionName == ".lq.RecordDiscardTile")
        {
        }
        else if (actionName == ".lq.RecordChiPengGang")
        {
        }
        else if (actionName == ".lq.RecordAnGangAddGang")
        {
        }
        else if (actionName == ".lq.RecordBaBei")
        {
        }
        else if (actionName == ".lq.RecordHule")
        {
            njson hules = actionData["hules"];
            const int num = hules.size();
            for (int i = 0; i < num; i++)
            {
                std::string type = hules[i]["zimo"].get<bool>() ? "自摸" : "荣胡";
                std::string comma = num > 1 && i != num ? "," : "";
                const int seat = hules[i]["seat"].get<int>();
                activeRound->addActs(
                    std::format("{}:{}{}", seats[seat], type, comma));
            }
        }
        else if (actionName == ".lq.RecordNoTile")
        {
        }
        else if (actionName == ".lq.RecordLiuJu")
        {
        }
        else std::cout << "未测试动作: " << actionName << std::endl;
    }
}

void MajongGame::parsePaifu()
{
    njson accounts = paifu["head"]["accounts"];
    seats.resize(accounts.size());
    for (const auto& account : accounts)
    {
        const int seat = account.contains("seat") ? account["seat"].get<int>() : 0;
        seats[seat] = account["nickname"].get<std::string>();
    }
    njson data = paifu["data"]["data"];
    if (data["version"] == 210715)
    {
        njson actions = data["actions"];
        actions_ptr = actions;
        // 存action;action
        for (const auto& action : actions)
        {
            if (action["type"].get<int>() == 1)
            {
                parseAction(action);
            }
        }
    }
}

void MajongGame::unloadPaifu() const
{
    delete(&paifu);
}

void MajongGame::resetPaifu(const std::string& fileName)
{
    if (fileName == "")
    {
        paifu = {};
        actions_ptr = {};
        rounds_text.clear();
        // actions_text.clear();
    }
    else
    {
        std::ifstream f(fileName);
        paifu = njson::parse(f);
        parsePaifu();
    }
}
