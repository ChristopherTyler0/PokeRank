#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "pokemon.h"
using namespace std;
int main() {
//read in data from pokemon type chart.csv
    ifstream inFile("pokemonTypeChart.csv");

    if(inFile.is_open()){
        string fileLine;
        getline(inFile,fileLine);

        string types [18] = {};

        //because of the way the table is formatted, the first value will be blank
        string blank;
        istringstream  stream(fileLine);
        getline(stream,blank,',');
        for(int i = 0 ; i < 18 ; i++) {
            getline(stream, types[i], ',');
        }

        //test successful reading
        /*
        for(const auto& text : types){
            cout << text << "." << endl;
        }
        */

        //now create the pokemon objects
        unordered_map <string,pokemon> pokeMap;

        //need to read in as a string
        string tempAttack;

        //int attackValues[18];
        unordered_map <string,int> attackValues;


        //for all 18 types..
        int i = 0;
        while(getline(inFile,fileLine)) {
            istringstream stream(fileLine);
            //..read in all 18 attack values

            //first data box is the type name, which is unused
            getline(stream, blank, ',');
            for (int j = 0; j < 18; j++) {
                getline(stream, tempAttack, ',');
                int attack = stoi(tempAttack);
                attackValues.emplace(types[j], attack);
            }
            pokemon newPokemon(types[i], 1, attackValues);
            pokeMap.emplace(types[i], newPokemon);
            i++;
            attackValues.clear();
        }
        //test successful object and map creation
        /*
        for(const auto&attacker : types){
            for(const auto&defender : types){
                cout << attacker << "->" << defender << ": " << pokeMap.at(attacker).getAttackVal(defender) << endl;
            }
        }*/

        int iterations;
        cout << "More iterations will take longer but approximate a more accurate answer" << endl;
        cout << "How many iterations should run? (suggested ~5-> 10,000) ";
        cin >> iterations;

        //Now, we reach the actual algorithm
        for(int i = 0 ; i < iterations ; i++){
            for(const auto&attacker : types){
                for(const auto&defender : types){
                    float defenderWeight = pokeMap.at(defender).getWeight();
                    float attackerWeight = pokeMap.at(attacker).getWeight();
                    switch(pokeMap.at(attacker).getAttackVal(defender)){
                        case 0:
                            //increment attacker weight
                            if(defenderWeight >= 0){
                                pokeMap.at(attacker).modWeight((0.01 * defenderWeight));
                            }
                            else{
                                pokeMap.at(attacker).modWeight((-0.01 / defenderWeight));
                            }
                            //decrement defender weight
                            if(attackerWeight >= 0){
                                pokeMap.at(defender).modWeight((-0.01 * attackerWeight));
                            }
                            else{
                                pokeMap.at(defender).modWeight((0.01 / attackerWeight));
                            }
                            break;
                        case 2:
                            //increment attacker weight
                            if(defenderWeight >= 0) {
                                pokeMap.at(attacker).modWeight((0.02 * defenderWeight));
                            }
                            else{
                                pokeMap.at(attacker).modWeight((-0.02 / defenderWeight));
                            }
                            //decrement defender weight
                            if(attackerWeight >= 0){
                                pokeMap.at(defender).modWeight((-0.02 * attackerWeight));
                            }
                            else {
                                pokeMap.at(defender).modWeight((0.02 / attackerWeight));
                            }
                            break;
                        case -2:
                            //decrement attacker weight
                            if(defenderWeight >= 0) {
                                pokeMap.at(attacker).modWeight((-0.02 * defenderWeight));
                            }
                            else{
                                pokeMap.at(attacker).modWeight((0.02 / defenderWeight));
                            }

                            //increment defender weight
                            if(attackerWeight >= 0){
                                pokeMap.at(defender).modWeight((0.02 * attackerWeight));
                            }
                            else {
                                pokeMap.at(defender).modWeight((-0.02 / attackerWeight));
                            }
                            break;
                        case -4:
                            //decrement attacker weight
                            if(defenderWeight >= 0){
                                pokeMap.at(attacker).modWeight((-0.04 * defenderWeight));
                            }
                            else {
                                pokeMap.at(attacker).modWeight((0.04 / defenderWeight));
                            }
                            //increment defender weight
                            if(attackerWeight >= 0){
                                pokeMap.at(defender).modWeight((0.04 * attackerWeight));
                            }
                            else {
                                pokeMap.at(defender).modWeight((-0.04 / attackerWeight));
                            }
                            break;
                    }
                }
            }
            //lock in weights for this iteration
            for(const auto&type : types){
                pokeMap.at(type).lockWeight();
            }

            //add points for ranking at the end
            //requires going through and ranking the types
            int j = 9;
            unordered_set<string> listed;
            for(const auto& allType : types){
                float max;
                string highestType;
                bool first = true;
                for(const auto& thisType : types){
                    if(listed.find(thisType) != listed.end()){
                        continue;
                    }
                    if(first){
                        max = pokeMap.at(thisType).getWeight();
                        highestType = thisType;
                        first = false;
                    }else if(pokeMap.at(thisType).getWeight() > max) {
                        max = pokeMap.at(thisType).getWeight();
                        highestType = thisType;
                    }
                }
                listed.insert(highestType);
                pokeMap.at(highestType).addWin(j);
                j--;
            }
        }

        //rank and print
        cout << endl;
        cout << "Ranked by point values or 'wins' from all iterations: " << endl;

        unordered_set<string> listed;
        int j = 1;
        for(const auto& allType : types){
            int max;
            string highestType;
            bool first = true;
            for(const auto& thisType : types){
                if(listed.find(thisType) != listed.end()){
                    continue;
                }
                if(first){
                    max = pokeMap.at(thisType).getWins();
                    highestType = thisType;
                    first = false;
                }else if(pokeMap.at(thisType).getWins() > max) {
                    max = pokeMap.at(thisType).getWins();
                    highestType = thisType;
                }
            }
            listed.insert(highestType);
            cout << j << ". " << highestType << " with " <<
                 pokeMap.at(highestType).getWins() << " points" <<endl;
            j++;
        }

        cout << endl;
        cout << "Ranked by weight value from the last single iteration..." << endl;
        cout << "Less accurate ranking, but still interesting to see..." << endl;
        cout << "(See readme for more info)" << endl;
        j = 1;
        listed.clear();
        for(const auto& allType : types){
            float max;
            string highestType;
            bool first = true;
            for(const auto& thisType : types){
                if(listed.find(thisType) != listed.end()){
                    continue;
                }
                if(first){
                    max = pokeMap.at(thisType).getWeight();
                    highestType = thisType;
                    first = false;
                }else if(pokeMap.at(thisType).getWeight() > max) {
                    max = pokeMap.at(thisType).getWeight();
                    highestType = thisType;
                }
            }
            listed.insert(highestType);
            cout << j << ". " << highestType << " with a weight of: "
                 << pokeMap.at(highestType).getWeight() << endl;
            j++;
        }

        cout << endl;
        cout << "*There are two different lists generated..." << endl;
        cout << "The first one at the top is the more accurate one ^^^" << endl;
        cout << "(The second list is mainly to get further insight on the calculations)" << endl;
    }
    else {
        cout << "err opening file";
    }

    return 0;
}
