#ifndef PROJET_CPP_BOARD_HPP
#define PROJET_CPP_BOARD_HPP
#include <iostream>
#include <vector>
#include "Case.hpp"


class Plateau {
private:
    int NumberPlayer;
    int size;
    std::vector<std::vector<Case>> board;
public:
    explicit Plateau(int nbr_player);
    int getsize() const;
    void initBoard();
    int giveCoord() const;
    void initTileExchange();
    void initTileStone();
    void initTileRobbery();
    std::vector<std::vector<Case>> getBoard();
    void placePlayer(int x, int y, int player);
    void changeEtatBonus(int x, int y);
    void placeStone(int x, int y, std::string type, std::string value);

    void
        createTile(int x, int y, std::string type, std::string value, int player,
            std::vector<std::vector<int>> currentPlayer,
            int index);
};


#endif //PROJET_CPP_BOARD_HPP