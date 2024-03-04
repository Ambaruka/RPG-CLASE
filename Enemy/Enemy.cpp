
#include "Enemy.h"
#include <iostream>
#include <algorithm>


using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, false) {
}

bool compareSpeed(Player *a, Player *b) {
    return a->getSpeed() > b->getSpeed();}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth());
    damage+=damage;
    if(getHealth() <= damage) {
        cout<<getName()<<" has died"<<endl;
    }
    else {
        cout<<getName()<<" has taken " << damage << " damage" << endl;
    }
}

Character* Enemy::getTarget(vector<Player*> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

bool Enemy::flee(vector<Player*> teamMembers) {
    sort(teamMembers.begin(), teamMembers.end(), compareSpeed);
    Player* fastestPlayer = teamMembers[0];
    bool fleed = false;
    if(this->getSpeed() > fastestPlayer->getSpeed()) {
        fleed =  true;
    }
    else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout<< "chance: " << chance << endl;
        fleed = chance > 99;
    }

    return fleed;
}


ActionResult Enemy::takeAction(vector<Player*>players) {

    Character* target = nullptr;
    bool fleed = false;
    getHealth();
    getDamage();

    if (damage<=(health*0.85)) {
        target = getTarget(players);
        doAttack(target);
    }
        else{
        srand(time(NULL));
        int chance = rand() % 100;

            if(chance<5){
                fleed = flee(players);
                if(fleed) {
                    cout<<"The enemy have fled"<<endl;
                }
                else {
                    target = getTarget(players);
                    doAttack(target);
                }

            }
        }




    return ActionResult(target, fleed);
}

