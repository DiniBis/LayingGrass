#include "Case.hpp"

Case::Case() {
    type = "empty";
    value = ".";
    player = 0;
}

std::string Case::getType() {
    return this->type;
}

std::string Case::getValue() {
    return this->value;
}

int Case::getPlayer() {
    return player;
}

int Case::getIndexTuile() {
    return indexTuile;
}

void Case::setType(std::string val) {
    type = val;
}
void Case::setValue(std::string val) {
    this->value = val;
}

void Case::setPlayer(int player) {
    this->player = player;
}


void Case::setEtatBonus(int etat) {
    etatBonus = etat;
}

int Case::getEtatBonus() {
    return this->etatBonus;
}

void Case::setIndexTuile(int index) {
    indexTuile = index;
}