#include "Tile.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <cmath>
#include <random>
#include <algorithm>
#include <windows.h>

using json = nlohmann::json;

// Constructeur
Tile::Tile(int numberPlayer) : numberPlayer(numberPlayer) {
    loadTilesFromJson("../tiles/tiles.json"); // Chargemement des tiles depuis le fichier JSON
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(tile.begin(), tile.end(), gen);
    set5tile();
}

void Tile::loadTilesFromJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filePath);
    }

    json j;
    file >> j;
    file.close();

    for (const auto& tileData : j["tiles"]) {
        tile.push_back(tileData["shape"].get<std::vector<std::vector<int>>>());
    }

    if (tile.empty()) {
        throw std::runtime_error("Aucune tile trouvée dans le fichier JSON !");
    }

    current_tile = tile[indice];
}

std::vector<std::vector<int>> Tile::getTile() {
    return current_tile;
}

void Tile::rotateTile() {
    std::vector<std::vector<int>> new_tile;
    for (int i = current_tile[0].size() - 1; i >= 0; i--) {
        std::vector<int> row;
        for (const auto& line : current_tile) {
            row.push_back(line[i]);
        }
        new_tile.push_back(row);
    }
    current_tile = new_tile;
    set5tile();
}

void Tile::changeTile() {
    indice++;
    int nbr_tuile = std::ceil(numberPlayer * 10.67);
    if (indice >= nbr_tuile) {
        indice = 0;
    }
    current_tile = tile[indice];
    set5tile();
}

void Tile::setIndice(int change) {
    indice += change - 1;
    changeTile();
    set5tile();
}

void Tile::set5tile() {
    list_next5_tiles.clear();
    int nbr_tuile = std::ceil(numberPlayer * 10.67);
    for (int i = 1; i < 6; i++) {
        list_next5_tiles.push_back(tile[(indice + i) % nbr_tuile]);
    }
}

// Afficher les 5 prochaines tiles
void Tile::show5tile() {
    int max_row = 0;

    std::cout << "\nTiles suivantes :\n\n";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (const auto& tiles : list_next5_tiles) {
        max_row = std::max(max_row, (int)tiles.size());
    }

    for (int line = 0; line < max_row; ++line) {
        for (const auto& tiles : list_next5_tiles) {
            if (line < tiles.size()) {
                for (int value : tiles[line]) {
                    SetConsoleTextAttribute(hConsole, value == 1 ? 255 : 0);
                    std::cout << (value == 1 ? "1" : "0");
                }
            } else {
                for (size_t i = 0; i < tiles[0].size(); ++i) {
                    SetConsoleTextAttribute(hConsole, 0);
                    std::cout << "0";
                }
            }
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "   ";
        }
        std::cout << "\n";
    }
}

void Tile::showTile() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "\nTile actuelle :\n\n";

    for (const auto& row : current_tile) {
        for (int value : row) {
            SetConsoleTextAttribute(hConsole, value == 1 ? 255 : 0);
            std::cout << (value == 1 ? "1" : "0");
        }
        std::cout << "\n";
    }
    SetConsoleTextAttribute(hConsole, 15);
}

int Tile::getIndice() const {
    return indice;
}

std::vector<std::vector<int>> Tile::getTilebyindice(int indice) {
    return tile[indice];
}
