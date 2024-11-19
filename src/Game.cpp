#include <windows.h>
#include <algorithm>
#include "Game.hpp"
#include "Case.hpp"
#include <cstdlib>
#include <iostream>


using namespace std;

bool check_tile(int x, int y);

Game::Game() : players(), plateau(players.getNumberPlayers()), tiles(players.getNumberPlayers()) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    displayBoard();
    placePlayer();
    while (numberRound != 9) {
        SetConsoleTextAttribute(hConsole, 7);
        displayBoard();
        std::cout << "" << std::endl;
        std::cout << "C'est au tour de " << this->players.getName(currentPlayer) << " ( Joueur " << currentPlayer << " ) - Round " << numberRound + 1 << " : " << std::endl;

        tiles.showTile();
        SetConsoleTextAttribute(hConsole, 7);
        tiles.show5tile();
        SetConsoleTextAttribute(hConsole, 7);


        std::cout << "Que voulez vous faire? " << std::endl;
        std::cout << "1. Placer une tuile" << std::endl;
        std::cout << "2. Tourner une tuile" << std::endl;
        int action = 3;
        std::vector<int> bonus = players.getBonus(currentPlayer);
        if (bonus[0] != 0) {
            std::cout << action << " - Utiliser bonus échange" << std::endl;
            action++;
        }
        if (bonus[1] != 0) {
            std::cout << action << " - Utiliser bonus stone" << std::endl;
            action++;
        }
        if (bonus[2] != 0) {
            std::cout << action << " - Utiliser bonus vol" << std::endl;
            action++;
        }
        int reponse;
        std::cin >> reponse;
        if (reponse == 1) {
            placeTile();
            nextPlayer();
            checkBonus();
            tiles.changeTile();
        }
        else if (reponse == 2) {
            tiles.rotateTile();
        }
        action = 3;
        if (bonus[0] != 0) {
            if (reponse == action) {
                std::cout << "Utilisation du bonus échange" << std::endl;
                useExchangeBonus();
            }
            action++;
        }
        if (bonus[1] != 0) {
            if (reponse == action) {
                std::cout << "Utilisation du bonus stone" << std::endl;
                placeStone();
                displayBoard();
            }
            action++;
        }
        if (bonus[2] != 0) {
            if (reponse == action) {
                std::cout << "Utilisation du bonus vol" << std::endl;
                useRobberyBonus();
            }
            action++;
        }
    }
    std::cout << "Fin : Posez votre dernière tuile !" << std::endl;
    int rep;
    std::cin.get();
    finally();
}



void Game::displayBoard() {
    std::vector<std::string> couleurs = { "Bleu", "Vert", "Rouge", "Jaune", "Rose", "Orange", "Violet", "Ciel", "Pomme" };
    std::vector<int> color = { 1,2,4,6,13,14,5,11,10 };


    std::cout << "Board: " << std::endl;
    std::cout << "    ";
    for (int i = 0; i < plateau.getBoard().size(); i++) {
        if (i + 1 < 10) {
            std::cout << i + 1 << "  ";
        }
        else {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < plateau.getBoard().size(); i++) {
        if (i + 1 < 10) {
            std::cout << i + 1 << "   ";
        }
        else {
            std::cout << i + 1 << "  ";
        }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int j = 0; j < plateau.getBoard()[i].size(); j++) {
            int k;
            if (plateau.getBoard()[i][j].getPlayer() != 0) {
                int player = plateau.getBoard()[i][j].getPlayer();
                std::string search_color = players.getColor(player);
                auto it = std::find(couleurs.begin(), couleurs.end(), search_color);
                k = color[std::distance(couleurs.begin(), it)];
            }
            else {
                k = 7;
            }
            SetConsoleTextAttribute(hConsole, k);
            std::cout << plateau.getBoard()[i][j].getValue() << "  ";
            SetConsoleTextAttribute(hConsole, 7);
        }
        std::cout << std::endl;
    }
}


void Game::placePlayer() {
    for (int i = 0; i < players.getNumberPlayers(); i++) {
        bool valid = true;
        while (valid) {
            int x, y;
            std::cout << "Joueur " << i + 1 << " : " << std::endl;
            std::cout << "Entre les coordonées de la case de départ: " << std::endl;
            std::cout << "x: ";
            std::cin >> x;
            std::cout << "y: ";
            std::cin >> y;
            x--;
            y--;
            if (x >= 0 && x < plateau.getsize() && y >= 0 && y < plateau.getsize()) {
                if (plateau.getBoard()[x][y].getType() == "empty") {
                    plateau.placePlayer(x, y, i + 1);
                    valid = false;
                }
                else {
                    std::cout << "Case occupée" << std::endl;
                }
            }
            else {
                std::cout << "Mauvais coordonées" << std::endl;
            }
        }
    }
}

void Game::placeTile() {
    int x, y;
    std::vector<std::string> alphabet = { "a","b","c","d","e","f","g","h","i" };
    std::cout << "Joueur " << currentPlayer << " : " << std::endl;
    std::cout << "Entrer les coordonées : " << std::endl;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    if (checkTile(x - 1, y - 1)) {
        plateau.createTile(x - 1, y - 1, "tile", alphabet[numberRound], currentPlayer, tiles.getTile(), tiles.getIndice());
    }
    else {
        std::cout << "Case occupée choisi une autre case !" << std::endl;
        placeTile();
    }

}

bool Game::checkTile(int x, int y) {
    std::vector<std::vector<Case>> board = plateau.getBoard();
    std::vector<std::vector<int>> current_tile = tiles.getTile();
    std::size_t site_tilex = current_tile.size();
    std::size_t site_tiley = current_tile[0].size();
    bool touch = false;
    for (size_t i = 0; i < site_tilex; ++i) {
        for (size_t j = 0; j < site_tiley; ++j) {
            if (current_tile[i][j] == 1) {
                if (x + i < plateau.getsize() &&
                    y + j < plateau.getsize()) {
                    if (board[x + i][y + j].getType() == "empty") {
                        if (checkOtherPlayer(x + i, y + j)) {
                            if (checkArround(x + i, y + j)) {
                                touch = true;
                            }
                        }
                        else {
                            std::cout << "Elle n'est pas adjacente" << std::endl;
                            return false;
                        }
                    }
                    else {
                        std::cout << "Une case est pleine" << std::endl;
                        return false;
                    }
                }
                else {
                    std::cout << "On dépasse du plateau" << std::endl;
                    return false;
                }
            }
        }

    }
    return touch;
}

bool Game::checkTileOtherTile(int x, int y, std::vector<std::vector<int>> current_tile) {
    std::vector<std::vector<Case>> board = plateau.getBoard();
    std::size_t site_tilex = current_tile.size();
    std::size_t site_tiley = current_tile[0].size();
    bool touch = false;
    for (size_t i = 0; i < site_tilex; ++i) {
        for (size_t j = 0; j < site_tiley; ++j) {
            if (current_tile[i][j] == 1) {
                if (x + i < plateau.getsize() &&
                    y + j < plateau.getsize()) {
                    if (board[x + i][y + j].getType() == "empty") {
                        if (checkOtherPlayer(x + i, y + j)) {
                            if (checkArround(x + i, y + j)) {
                                touch = true;
                            }
                        }
                        else {
                            std::cout << "Non-adjacent" << std::endl;
                            return false;
                        }
                    }
                    else {
                        std::cout << "Une case est pleine" << std::endl;
                        return false;
                    }
                }
                else {
                    std::cout << "On dépasse du plateau" << std::endl;
                    return false;
                }
            }
        }

    }
    return touch;
}

bool Game::checkOtherPlayer(int x, int y) {
    std::vector<std::vector<Case>> board = plateau.getBoard();
    if (x + 1 < plateau.getsize()) {
        if (board[x + 1][y].getPlayer() != 0 && board[x + 1][y].getPlayer() != currentPlayer) {
            return false;
        }
    }
    if (x - 1 > 0) {
        if (board[x - 1][y].getPlayer() != 0 && board[x - 1][y].getPlayer() != currentPlayer) {
            return false;
        }
    }
    if (y + 1 < plateau.getsize()) {
        if (board[x][y + 1].getPlayer() != 0 && board[x][y + 1].getPlayer() != currentPlayer) {
            return false;
        }
    }
    if (y - 1 > 0) {
        if (board[x][y - 1].getPlayer() != 0 && board[x][y - 1].getPlayer() != currentPlayer) {
            return false;
        }
    }
    return true;
}

bool Game::checkArround(int x, int y) {
    std::vector<std::vector<Case>> board = plateau.getBoard();
    if (x + 1 < plateau.getsize()) {
        if (board[x + 1][y].getPlayer() == currentPlayer) {
            return true;
        }
    }
    if (x - 1 > 0) {
        if (board[x - 1][y].getPlayer() == currentPlayer) {
            return true;
        }
    }
    if (y + 1 < plateau.getsize()) {
        if (board[x][y + 1].getPlayer() == currentPlayer) {
            return true;
        }
    }
    if (y - 1 > 0) {
        if (board[x][y - 1].getPlayer() == currentPlayer) {
            return true;
        }
    }
    return false;
}


bool Game::checkEmpty(int x, int y) {
    if (plateau.getBoard()[x][y].getType() == "empty") {
        return true;
    }
    else {
        return false;
    }
}


void Game::nextPlayer() {
    if (currentPlayer == players.getNumberPlayers()) {
        currentPlayer = 1;
        numberRound++;
    }
    else {
        currentPlayer++;
    }
}

void Game::checkBonus() {
    for (int x = 0; x < plateau.getsize(); x++) {
        for (int y = 0; y < plateau.getsize(); y++) {
            if (plateau.getBoard()[x][y].getValue() == "E" || plateau.getBoard()[x][y].getValue() == "S" || plateau.getBoard()[x][y].getValue() == "R") {
                if (plateau.getBoard()[x][y].getEtatBonus() == 0) {
                    int first = 0;
                    bool error = false;
                    for (int i = -1; i < 2; i++) {
                        for (int j = -1; j < 2; j++) {
                            if (x + (i) != x && y + (j) != y) {
                                if (x + (i) > 0 && x + (i) < plateau.getsize() && y + (j) > 0 &&
                                    y + (j) < plateau.getsize()) {
                                    if (first == 0) {
                                        first = plateau.getBoard()[x + (i)][y + (j)].getPlayer();
                                    }
                                    else if (plateau.getBoard()[x + (i)][y + (j)].getPlayer() != first) {
                                        error = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (error || first == 0) {
                            error = true;
                            break;
                        }
                    }
                    if (!error) {
                        plateau.changeEtatBonus(x, y);
                        players.setBonus(currentPlayer, plateau.getBoard()[x][y].getValue());
                    }
                    else {
                    }
                }
            }
        }
    }
}

void Game::useExchangeBonus() {
    cout << "Que voulez vous faire ?" << endl;
    cout << "1. Changer de tuile " << endl;
    cout << "2. Echanger une rocher " << endl;
    int reponse;
    cin >> reponse;

    if (reponse == 1) {
        cout << "Quelle tuile voulez vous prendre ? (1,2,3,4,5)" << endl;
        int reponse2;
        cin >> reponse2;
        if (reponse2 >= 1 && reponse2 <= 5) {
            tiles.setIndice(reponse2);
            players.setBonusDimin(currentPlayer, "E");
        }

    }
    else if (reponse == 2) {
        remooveStone();
    }

}

void Game::placeStone() {
    int x, y;
    std::cout << "Entrez les coordonées pour la roche : " << std::endl;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    if (plateau.getBoard()[x - 1][y - 1].getType() == "empty") {
        plateau.placeStone(x - 1, y - 1, "stone", "s");
        players.setBonusDimin(currentPlayer, "S");
    }
    else {
        std::cout << "Case occupé, Choisi une autre case !" << std::endl;
        placeStone();
    }
}

void Game::remooveStone() {
    int x, y;
    std::cout << "Entrez les coordonées pour la roche : " << std::endl;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    if (plateau.getBoard()[x - 1][y - 1].getType() == "stone") {
        plateau.placeStone(x - 1, y - 1, "empty", " ");
        players.setBonusDimin(currentPlayer, "S");
    }
    else {
        std::cout << "Case occupé, Choisi une autre case !" << std::endl;
        remooveStone();
    }
}

void Game::useRobberyBonus() {
    int x, y;
    std::cout << "Entrez les coordonées de la tuile à voler : " << std::endl;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    if (plateau.getBoard()[x - 1][y - 1].getType() == "tile") {
        int player = plateau.getBoard()[x - 1][y - 1].getPlayer();
        int indice = plateau.getBoard()[x - 1][y - 1].getIndexTuile();
        std::string value = plateau.getBoard()[x - 1][y - 1].getValue();
        for (int i = 0; i < plateau.getsize(); i++) {
            for (int j = 0; j < plateau.getsize(); j++) {
                if (plateau.getBoard()[i][j].getPlayer() == player && plateau.getBoard()[i][j].getValue() == value && plateau.getBoard()[i][j].getIndexTuile() == indice) {
                    plateau.placeStone(i, j, "empty", ".");
                }
            }
        }
        std::cout << "Entrez les coordonées pour la nouvelle tuile : " << std::endl;
        std::cout << "x: ";
        std::cin >> x;
        std::cout << "y: ";
        std::cin >> y;
        if (x < plateau.getsize() && y < plateau.getsize()) {
            if (checkTileOtherTile(x - 1, y - 1, tiles.getTilebyindice(indice))) {
                plateau.createTile(x - 1, y - 1, "tile", "v", currentPlayer, tiles.getTilebyindice(indice), indice);
                players.setBonusDimin(currentPlayer, "R");
            }
            else {
                std::cout << "Case occupé, Choisi une autre case !" << std::endl;
            }
        }
        else {
            std::cout << "Case invalide !" << std::endl;
            useRobberyBonus();
        }
    }
    else {
        std::cout << "Case invalide !" << std::endl;
        useRobberyBonus();
    }

}

void Game::placeLastTile() {
    std::vector<std::string> alphabet = { "a","b","c","d","e","f","g","h","i","j" };
    for (int i = 0; i < players.getNumberPlayers(); i++) {
        bool valid = true;
        while (valid) {
            int x, y;
            std::cout << "Joueur " << i + 1 << " : " << std::endl;
            std::cout << "Entrez les coordonées de votre dernier tuile de 1*1: " << std::endl;
            std::cout << "x: ";
            std::cin >> x;
            std::cout << "y: ";
            std::cin >> y;
            x--;
            y--;
            if (x >= 0 && x < plateau.getsize() && y >= 0 && y < plateau.getsize()) {
                if (plateau.getBoard()[x][y].getType() == "empty") {
                    plateau.createTile(x, y, "tile", alphabet[i], i + 1, { {1} }, -1);
                    valid = false;
                }
                else {
                    std::cout << "Case occupée" << std::endl;
                }
            }
            else {
                std::cout << "Coordonnées invalides" << std::endl;
            }
        }
        displayBoard();
    }
}

void Game::finally() {
    placeLastTile();
    std::cout << "Résultat : " << std::endl;
    int score_max = 0;
    std::vector<int> player_max = {};
    for (int i = 0; i < plateau.getsize(); i++) {
        for (int j = 0; j < plateau.getsize(); j++) {
            if (plateau.getBoard()[i][j].getPlayer() != 0) {
                int player = plateau.getBoard()[i][j].getPlayer();
                int square_size = calculScore(i, j, player);
                if (square_size > score_max) {
                    score_max = square_size;
                    player_max.clear();
                    player_max.push_back(player);
                }
                else if (square_size == score_max) {
                    bool estPresent = false;
                    for (int element : player_max) {
                        if (element == player) {
                            estPresent = true;
                            break;
                        }
                    }
                    if (!estPresent) {
                        player_max.push_back(player);
                    }
                }
            }
        }
    }
    int length = 25;
    int height = (length - 1) / 2;
    crown(length, height);

    if (player_max.size() > 1) {
        std::cout << "Egalité entre les joueurs ";
        for (int i = 0; i < player_max.size(); i++) {
            std::cout << player_max[i] << " ";
        }
        std::cout << std::endl;
    }
    else if (player_max.size() == 1) {
        std::cout << "Vainqueur " << player_max[0] << std::endl;
    }
    std::cout << "Meilleur score : " << score_max << std::endl;
};

int Game::calculScore(int x, int y, int player) {
    if (plateau.getBoard()[x][y].getPlayer() != player) {
        return 0;
    }
    else {
        int a = calculScore(x + 1, y, player);
        int b = calculScore(x, y + 1, player);
        int c = calculScore(x + 1, y + 1, player);
        return min(min(a, b), c) + 1;;
    }
};

void Game::crown(int length, int height)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            if (i == 0) {
                if (j == 0 || j == height || j == length - 1) {
                    cout << "*";
                }
                else {
                    cout << " ";
                }
            }
            else if (i == height - 1) {
                cout << "*";
            }
            else if ((j < i || j > height - i) &&
                (j < height + i || j >= length - i))
                cout << "#";
            else
                cout << " ";
        }
        cout << "\n";
    }
}


