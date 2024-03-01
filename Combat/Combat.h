

#ifndef RPG_COMBAT_H
#define RPG_COMBAT_H
#pragma once
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Player/ActionResult.h"
#include <vector>
#include <string>

using namespace std;

class Player;
class Enemy;

class Combat {
private:
    vector<Character*> participants;
    vector<Player*> teamMembers;
    vector<Enemy*> enemies;
    void prepareCombat();
    Character* getTarget(Character* target);
public:
    Combat(vector<Character*> _participants);
    Combat(vector<Player*> _teamMembers);
    Combat(vector<Enemy*> _enemies);
    Combat();
    void addParticipant(Character *participant);
    void doCombat();
    string participantsToString();
};


#endif //RPG_COMBAT_H
