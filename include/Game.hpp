#ifndef PROJET_CPP_GAME_H
#define PROJET_CPP_GAME_H

#include "Party.hpp"
#include "Board.hpp"
#include "Tile.hpp"
#include <iostream>

class Game {
private:
    Players players;
    Plateau plateau;
    Tile tiles;
    int currentPlayer = 1;
    int numberRound = 0;
public:
    Game();
    void displayBoard();
    void placePlayer();
    void placeTile();
    bool checkTile(int x, int y);
    bool checkOtherPlayer(int x, int y);
    bool checkArround(int x, int y);
    bool checkEmpty(int x, int y);
    void nextPlayer();
    void checkBonus();
    void useExchangeBonus();
    void placeStone();
    void remooveStone();
    void finally();
    void calculScore();
    int checkLigne(int x, int y, int player);
    int calculScore(int x, int y, int player);
    void crown(int length, int height);
    void placeLastTile();
    void useRobberyBonus();
    bool checkTileOtherTile(int x, int y, std::vector<std::vector<int>> current_tile);
};


#endif //PROJET_CPP_GAME_H
