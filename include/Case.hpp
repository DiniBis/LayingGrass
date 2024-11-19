#ifndef PROJET_CPP_CASE_HPP
#define PROJET_CPP_CASE_HPP
#include <iostream>

class Case {
private:
    std::string type;
    std::string value;
    int player;
    int indexTuile;
    int etatBonus;
public:
    Case();
    std::string getType();
    std::string getValue();
    int getPlayer();
    void setType(std::string type);
    void setValue(std::string value);
    void setPlayer(int player);
    void setIndexTuile(int index);
    void setEtatBonus(int etat);
    int getEtatBonus();
    int getIndexTuile();
};


#endif //PROJET_CPP_CASE_HPP
