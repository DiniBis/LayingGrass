#include "Board.hpp"
#include <random>
#include <string>
#include <cmath>
#include <utility>

Plateau::Plateau(int NumberPlayer) : NumberPlayer(NumberPlayer) {
    initBoard();
    initTileExchange();
    initTileStone();
    initTileRobbery();
}

std::vector<std::vector<Case>> Plateau::getBoard() {
    return board;
}

void Plateau::initBoard() {
    if (NumberPlayer <= 4) {
        size = 20;
    }
    else {
        size = 30;
    }
    for (int i = 0; i < size; ++i) {
        std::vector<Case> row;
        for (int j = 0; j < size; ++j) {
            row.push_back(Case());
        }
        board.push_back(row);
    }
    std::cout << "Le plateau est build en" << size << "*" << size << std::endl;
}

int Plateau::giveCoord() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    int i = dis(gen);
    return i;
}

void Plateau::initTileExchange() {
    double nbr_case = 1.5 * NumberPlayer;
    double nombreArrondi = std::ceil(nbr_case);
    for (int i = 0; i < nombreArrondi; i++) {
        bool its_ok = true;
        while (its_ok) {
            int x = giveCoord();
            int y = giveCoord();
            if (board[x][y].getType() == "empty") {
                its_ok = false;
                board[x][y].setType("exchange");
                board[x][y].setValue("E");
                board[x][y].setEtatBonus(0);
            }
        }
    }
}

void Plateau::initTileStone() {
    double nbr_case = 0.5 * NumberPlayer;
    double nombreArrondi = std::ceil(nbr_case);
    for (int i = 0; i < nombreArrondi; i++) {
        bool its_ok = true;
        while (its_ok) {
            int x = giveCoord();
            int y = giveCoord();
            if (board[x][y].getType() == "empty") {
                its_ok = false;
                board[x][y].setType("stone");
                board[x][y].setValue("S");
                board[x][y].setEtatBonus(0);
            }
        }
    }
}

void Plateau::initTileRobbery() {
    double nbr_case = 1 * NumberPlayer;
    for (int i = 0; i < nbr_case; i++) {
        bool its_ok = true;
        while (its_ok) {
            int x = giveCoord();
            int y = giveCoord();
            if (board[x][y].getType() == "empty") {
                its_ok = false;
                board[x][y].setType("robbery");
                board[x][y].setValue("R");
                board[x][y].setEtatBonus(0);
            }
        }
    }
}

void Plateau::placePlayer(int x, int y, int player) {
    board[x][y].setType("start");
    board[x][y].setValue(std::to_string(player));
    board[x][y].setPlayer(player);
}

void Plateau::placeStone(int x, int y, std::string type, std::string value) {
    board[x][y].setType(type);
    board[x][y].setValue(value);
}

void Plateau::createTile(int x, int y, std::string type, std::string value, int player, std::vector<std::vector<int>> current_player, int index) {
    for (size_t i = 0; i < current_player.size(); ++i) {
        for (size_t j = 0; j < current_player[i].size(); ++j) {
            if (current_player[i][j] == 1) {
                board[x + i][y + j].setType(type);
                board[x + i][y + j].setValue(value);
                board[x + i][y + j].setPlayer(player);
                board[x + i][y + j].setIndexTuile(index);
            }
        }
    }
}

int Plateau::getsize() const {
    return size;
}

void Plateau::changeEtatBonus(int x, int y) {
    board[x][y].setEtatBonus(1);
}







