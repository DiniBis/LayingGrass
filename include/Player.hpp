#ifndef PROJECT_2CPP_PLAYER_HPP
#define PROJECT_2CPP_PLAYER_HPP
#include <iostream>


class Player {
private:
    int numberPlayer;
    std::string name;
    std::string color;
    int bonus_exchange = 1;
    int bonus_stone = 1;
    int bonus_robbery = 1;

public:
    Player(int num_player, std::string name, std::string color);
    void indent_bonus_exchange();
    void indent_bonus_stone();
    void indent_bonus_robbery();
    void dimin_bonus_exchange();
    void dimin_bonus_stone();
    void dimin_bonus_robbery();
    int getPlayerNumber() const;
    std::string getName();
    std::string getColor();
    int getExchangeBonus() const;
    int getStoneBonus() const;
    int getRobberyBonus() const;
};


#endif //PROJECT_2CPP_PLAYER_HPP
