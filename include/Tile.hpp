#ifndef PROJECT_2CPP_TILE_HPP
#define PROJECT_2CPP_TILE_HPP

#include <iostream>
#include <vector>
#include <string>

class Tile {
private:
    int indice = 0;
    std::vector<std::vector<std::vector<int>>> tile;
    std::vector<std::vector<std::vector<int>>> list_next5_tiles;
    std::vector<std::vector<int>> current_tile;
    int numberPlayer;

public:
    Tile(int numberPlayer);
    std::vector<std::vector<int>> getTile();
    void changeTile();
    void rotateTile();
    void setIndice(int change);
    void show5tile();
    void set5tile();
    void showTile();
    int getIndice() const;
    std::vector<std::vector<int>> getTilebyindice(int indice);
    void loadTilesFromJson(const std::string& filePath);
};

#endif // PROJECT_2CPP_TILE_HPP
