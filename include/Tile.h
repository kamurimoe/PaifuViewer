#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class Tile {
    int number;
    char type;

    static bool isValidType(const char t) {
        return t == 'm' || t == 'p' || t == 's' || t == 'z';
    }

    static bool isValidNumber(const int n, const char t) {
        if (t == 'z') {
            return n >= 1 && n <= 7;
        }
        return n >= 0 && n <= 9;
    }

public:
    // 基本构造函数
    Tile(const int n, const char t) {
        if (!isValidType(t) || !isValidNumber(n, t)) {
            throw std::invalid_argument("Invalid tile");
        }
        number = n;
        type = t;
    }

    // 字符串构造函数
    explicit Tile(const std::string& str) {
        if (str.length() != 2) {
            throw std::invalid_argument("Invalid tile string format");
        }

        const int n = str[0] - '0';
        const char t = str[1];

        if (!isValidType(t) || !isValidNumber(n, t)) {
            throw std::invalid_argument("Invalid tile");
        }

        number = n;
        type = t;
    }

    [[nodiscard]] int getNumber() const { return number; }
    [[nodiscard]] char getType() const { return type; }

    [[nodiscard]] std::string toString() const {
        return std::string(1, static_cast<char>(number + '0')) + type;
    }

    bool operator==(const Tile& other) const {
        return number == other.number && type == other.type;
    }

    bool operator<(const Tile& other) const {
        if (type != other.type) {
            return type < other.type;
        }
        return number < other.number;
    }
};

class Tiles {
    std::vector<Tile> tiles;

public:
    Tiles() = default;

    explicit Tiles(const std::string& str) {
        if (str.empty() || str.length() % 2 != 0) {
            throw std::invalid_argument("Invalid tiles string format");
        }

        for (size_t i = 0; i < str.length(); i += 2) {
            tiles.emplace_back(str.substr(i, 2));
        }
    }

    void addTile(const Tile& tile) {
        tiles.push_back(tile);
    }

    [[nodiscard]] const std::vector<Tile>& getTiles() const {
        return tiles;
    }

    [[nodiscard]] std::string toString() const {
        std::string result;
        for (const auto& tile : tiles) {
            result += tile.toString();
        }
        return result;
    }

    [[nodiscard]] size_t size() const {
        return tiles.size();
    }

    void clear() {
        tiles.clear();
    }

    const Tile& operator[](const size_t index) const {
        return tiles[index];
    }

    Tile& operator[](size_t index) {
        return tiles[index];
    }
};