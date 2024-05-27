//
// Created by Chris Tyler on 10/21/23.
//
#include "pokemon.h"
#include <string>
#include <unordered_map>
using namespace std;

pokemon :: pokemon(string type, float weight, unordered_map<string, int> attackValues) {
    this-> type = type;
    this-> weight= weight;
    this-> tempWeight = weight;
    this-> attackVales = attackValues;
    this-> winCount = 0;
}
pokemon :: pokemon() {
    this-> weight = 1;
    this-> tempWeight = 1;
    this->winCount = 0;
}

float pokemon ::getWeight() {
    return weight;
}
int pokemon::getAttackVal(string type) {
    return attackVales.at(type);
}

string pokemon ::getType() {
    return type;
}

void pokemon::modWeight(float modify) {
    this->tempWeight += modify;
}

void pokemon::lockWeight() {
    this->weight = this->tempWeight;
}

void pokemon::addWin(int inc) {
    this->winCount += inc;
}
int pokemon::getWins() {
    return winCount;
}

