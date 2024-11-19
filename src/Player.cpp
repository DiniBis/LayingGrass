#include "Player.hpp"

Player::Player(int numberPlayer, std::string name, std::string color) : numberPlayer(numberPlayer), name(std::move(name)), color(std::move(color)) {
}

void Player::indent_bonus_exchange() {
    bonus_exchange++;
}

void Player::indent_bonus_stone() {
    bonus_stone++;
}

void Player::indent_bonus_robbery() {
    bonus_robbery++;
}

void Player::dimin_bonus_exchange() {
    bonus_exchange--;
}

void Player::dimin_bonus_stone() {
    bonus_stone--;
}

void Player::dimin_bonus_robbery() {
    bonus_robbery--;
}

int Player::getPlayerNumber() const {
    return numberPlayer;
}

std::string Player::getName() {
    return name;
}

std::string Player::getColor() {
    return this->color;
}

int Player::getExchangeBonus() const {
    return bonus_exchange;
}

int Player::getStoneBonus() const {
    return bonus_stone;
}

int Player::getRobberyBonus() const {
    return bonus_robbery;
}