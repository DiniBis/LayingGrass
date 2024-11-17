#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <windows.h>
#include <vector>

using json = nlohmann::json;
using namespace std;

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    SetConsoleOutputCP(65001);
    // Ouvrir le fichier JSON
    ifstream file("C:/Users/thoma/CLionProjects/PROJECT_2CPP/tiles/tiles.json");
    if (!file.is_open()) {
        cerr << "Impossible d'ouvrir le fichier JSON" << endl;
        return 1;
    }

    // Charger le JSON dans un objet
    json j;
    file >> j;

    // Parcourir les tiles et afficher les shapes
    if (j.contains("tiles") && j["tiles"].is_array()) {
        int tile_index = 0;
        for (const auto& tile : j["tiles"]) {
            cout << "Tile " << tile_index << ":\n";
            if (tile.contains("shape") && tile["shape"].is_array()) {
                for (const auto& row : tile["shape"]) {
                    for (const auto& cell : row) {
                        setConsoleColor(10);
                        if (cell == 0) {
                            cout << "  ";
                        } else {
                            cout << "██";
                        }
                        setConsoleColor(7);
                    }
                    cout << endl;
                }
            }
            cout << endl;
            tile_index++;
        }
        system("PAUSE");
    } else {
        cerr << "Le JSON ne contient pas de tableau 'tiles' valide." << endl;
    }
    setConsoleColor(7);
    file.close();
    return 0;
}
