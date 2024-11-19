#ifndef PROJET_CPP_PLAYERS_HPP
#define PROJET_CPP_PLAYERS_HPP
#include <iostream>
#include <vector>
#include "Player.hpp"


class Players {
private:
    int numberPlayers;
    std::vector<Player> players;
public:
    Players();
    int getNumberPlayers() const;
    static std::vector<Player> getPlayers();
    void initPlayers();
    void setBonus(int numberPlayers, const std::string& bonus);
    std::string getColor(int numberPlayers);
    std::string getName(int numberPlayers);
    std::vector<int> getBonus(int numberPlayers);
    void setBonusDimin(int numberPlayers, const std::string& bonus);
};


#endif //PROJET_CPP_PLAYERS_HPP
