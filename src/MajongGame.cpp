#include "MajongGame.h"
#include <fstream>
#include <format>
#include <iostream>

const std::string seat_order[] = {"东", "南", "西", "北"};

int findHouju(njson arr)
{
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] < 0)
            return i;
    return -1;
}

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
    if (i == -1)return &Rounds.back();
    return &Rounds[i];
}

void MajongGame::parseAction(const njson& a)
{
    const std::string actionName = a["result"]["name"].get<std::string>();
    njson actionData = a["result"]["data"];
    if (actionName == ".lq.RecordNewRound")
    {
        const int chang = actionData["chang"].get<int>();
        const int ju = actionData["ju"].get<int>();
        const int ben = actionData["ben"].get<int>();
        if (!rounds_text.empty())rounds_text += ";";
        rounds_text += std::format("{}{}局{}本场", seat_order[chang], ju, ben);
        Rounds.emplace_back(actionData["paishan"].get<std::string>());
    }
    else
    {
        Round* activeRound = getRound(-1);
        const int seat = actionData["seat"].get<int>();
        const std::string name = seats[seat];
        if (actionName == ".lq.RecordDealTile")
        {
            activeRound->addActs(std::format("{}:摸{}", name, actionData["tile"].get<std::string>()));
        }
        else if (actionName == ".lq.RecordDiscardTile")
        {
            activeRound->addActs(
                std::format("{}:切{}{}", name, actionData["tile"].get<std::string>(),
                            actionData["is_wliqi"].get<bool>()
                                ? "双立直"
                                : actionData["is_liqi"].get<bool>()
                                ? "立直"
                                : ""));
        }
        else if (actionName == ".lq.RecordChiPengGang")
        {
            const int type = actionData["type"].get<int>();
            const auto tiles = actionData["tiles"].get<std::vector<std::string>>();
            std::string act =
                type == 0 ? tiles[0] + tiles[1] + "吃" + tiles[2] : type == 1 ? "碰" + tiles[0] : "杠" + tiles[0];

            activeRound->addActs(
                std::format("{}:{}({})", name, act,
                            seats[actionData["froms"][actionData["froms"].size() - 1].get<int>()]));
        }
        else if (actionName == ".lq.RecordAnGangAddGang")
        {
            const int type = actionData["type"].get<int>();
            const auto tile = actionData["tiles"][0].get<std::string>();
            std::string act =
                type == 2 ? "加杠" + tile : "暗杠" + tile;

            activeRound->addActs(
                std::format("{}:{}", name, act));
        }
        else if (actionName == ".lq.RecordBaBei")
        {
            activeRound->addActs(
                std::format("{}:拔北", name));
        }
        else if (actionName == ".lq.RecordHule")
        {
            njson hules = actionData["hules"];
            const auto num = hules.size();
            for (int i = 0; i < num; i++)
            {
                std::string type =
                    hules[i]["zimo"].get<bool>() ? "自摸" : "荣胡" + seats[findHouju(actionData["delta_scores"])];
                std::string comma = num > 1 && i != num ? ";" : "";
                const int hule_seat = hules[i]["seat"].get<int>();
                activeRound->addActs(
                    std::format("{}:{}{}", seats[hule_seat], type, comma));
            }
        }
        else if (actionName == ".lq.RecordNoTile")
        {
            if (actionData["liujumanguan"].get<bool>())
            {
                njson scores = actionData["scores"];
                std::string liumans;
                for (const auto& score : scores)
                {
                    if (!liumans.empty())liumans += "&";
                    liumans += seats[score["seat"].get<int>()];
                }
                activeRound->addActs(
                    std::format("{}:流局满贯", liumans));
            }
            else
            {
                activeRound->addActs("荒牌流局");
            }
        }
        else if (actionName == ".lq.RecordLiuJu")
        {
            const int type = actionData["type"].get<int>();
            activeRound->addActs(
                type == 1 ? std::format("{}:九种九牌", name) : type == 2 ? "四风连打" : type == 3 ? "四杠散了" : "四家立直"
            );
        }
        else std::cout << "未测试到该行为: " << actionName << std::endl;
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
    if (njson data = paifu["data"]["data"]; data["version"] == 210715)
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
    paifu.clear();
    actions_ptr.clear();
    rounds_text.clear();
    Rounds.clear();
    seats.clear();

    std::ifstream f(fileName);
    paifu = njson::parse(f);
    parsePaifu();
}
