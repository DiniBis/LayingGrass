#include <iostream>
#include <algorithm>
#include "Party.hpp"


Players::Players() {
    bool good_nbr_player = true;
    while (good_nbr_player) {
        std::cout << "Veuillez indiquer le nombre total de joueur : ";
        std::cin >> numberPlayers;
        if (numberPlayers > 1 && numberPlayers < 10) {
            good_nbr_player = false;
        }
        else {
            std::cout << "Le nombre de joueur doit être entre 2 et 9 joueurs au maximum" << std::endl;
        }
    }
    initPlayers();
}

int Players::getNumberPlayers() const {
    return numberPlayers;
}

std::vector<Player> Players::getPlayers() {
    return std::vector<Player>();
}

void Players::initPlayers() {
    std::vector<std::string> couleurs = { "Rouge", "Vert", "Bleu", "Jaune", "Rose", "Orange", "Violet", "Ciel", "Pomme" };
    for (int i = 0; i < numberPlayers; ++i) {
        std::cout << "Nom du joueur " << i + 1 << std::endl;
        std::string name;
        std::cin >> name;

        std::cout << "Liste des couleurs disponibles : ";
        for (const std::string& couleur : couleurs) {
            std::cout << couleur << " ";
        }
        std::cout << std::endl;

        bool valid_color = false;
        std::string color;

        while (!valid_color) {
            std::cout << "Couleur du joueur " << i + 1 << std::endl;
            std::cin >> color;

            auto index = std::find(couleurs.begin(), couleurs.end(), color);

            if (index != couleurs.end()) {
                std::cout << "Couleur valide" << std::endl;
                couleurs.erase(index);
                valid_color = true;
            }
            else {
                std::cout << "Couleur non valide." << std::endl;
            }
        }
        players.emplace_back(i + 1, name, color);
    }
}

void Players::setBonus(int num_player, const std::string& bonus) {
    if (bonus == "E") {
        players[num_player - 1].indent_bonus_exchange();
    }
    else if (bonus == "S") {
        players[num_player - 1].indent_bonus_stone();
    }
    else if (bonus == "R") {
        players[num_player - 1].indent_bonus_robbery();
    }
}

void Players::setBonusDimin(int num_player, const std::string& bonus) {
    if (bonus == "E") {
        players[num_player - 1].dimin_bonus_exchange();
    }
    else if (bonus == "S") {
        players[num_player - 1].dimin_bonus_stone();
    }
    else if (bonus == "R") {
        players[num_player - 1].dimin_bonus_robbery();
    }
}

std::string Players::getColor(int num_player) {
    return players[num_player - 1].getColor();
}

std::string Players::getName(int num_player) {
    return players[num_player - 1].getName();
}

std::vector<int> Players::getBonus(int num_player) {
    std::vector<int> bonus;
    bonus.push_back(players[num_player - 1].getExchangeBonus());
    bonus.push_back(players[num_player - 1].getStoneBonus());
    bonus.push_back(players[num_player - 1].getRobberyBonus());
    return bonus;
}
