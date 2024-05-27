//
// Created by Chris Tyler on 10/21/23.
//

#ifndef POKEMONTYPERANK_POKEMON_H
#define POKEMONTYPERANK_POKEMON_H
#include <string>
#endif //POKEMONTYPERANK_POKEMON_H
#include<unordered_map>


using namespace std;

class pokemon{
private:
    string type;
    float weight;
    float tempWeight;
    int winCount;
    unordered_map <string, int> attackVales;
public:
    //constructor
    pokemon(string type, float weight, unordered_map <string, int> attackValues);
    //default constructor
    pokemon();

    //accessor
    float getWeight();
    int getAttackVal(string type);
    string getType();
    int getWins();

    //mutator
    void modWeight(float modify);
    void lockWeight();
    void addWin(int inc);

};