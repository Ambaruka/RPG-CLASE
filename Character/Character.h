

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include<string>

using namespace std;

class Character {
protected:
    string name;
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool isEnemy;
    int damage;

public:
    Character(string, int, int, int, int, bool);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    void setName(string);
    string getName();
    void setHealth(int);
    int getHealth();
    void setAttack(int);
    int getAttack();
    void setDefense(int);
    int getDefense();
    void setSpeed(int);
    int getSpeed();
    string toString();
    bool getIsPlayer();
    bool getIsEnemy();
    void setDamage(int);
    int getDamage();
};


#endif //RPG_CHARACTER_H
