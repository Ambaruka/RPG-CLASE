
#include "Combat.h"
#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

class Combat;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    teamMembers = std::move(teamMembers);
    enemies = std::move(enemies);
    //duda com std::move()
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}

void Combat::doCombat() {
    prepareCombat();

    while(enemies.size() != 0 && teamMembers.size() != 0) {
        vector<Character*>::iterator participant = participants.begin();

        while(participant != participants.end()) {
            Character* target = nullptr;
            if((*participant)->getIsPlayer()){
                ActionResult playerAction = ((Player*)*participant)->takeAction(enemies);
                if(playerAction.target && playerAction.target->getHealth() <= 0) {
                    participant = participants.erase(remove(participants.begin(), participants.end(), playerAction.target), participants.end());
                    enemies.erase(remove(enemies.begin(), enemies.end(), playerAction.target), enemies.end());
                } else if (playerAction.fleed) {
                    return;
                } else {
                    participant++;
                }
            }
            else {
                while(participant != participants.end()) {
                    Character* target = nullptr;
                    if((*participant)->getIsEnemy())
                    {
                        ActionResult enemyAction =((Enemy*)*participant)->takeAction(teamMembers);
                        if((*participant)->getHealth() <= 0) {
                            participant = participants.erase(remove(participants.begin(), participants.end(), enemyAction.target), participants.end());
                            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), enemyAction.target), teamMembers.end());
                        } else if (enemyAction.fleed) {
                            return;
                        }
                        else {
                            participant++;
                        }
            }

        }
    }
        }

    //No se imprime el nombre del ganador
    if(enemies.size() == 0) {
        cout<<"You have won the combat"<<endl;
    }
    else {
        cout<<"The enemies have won the combat - Game Over"<<endl;
    }
}

string Combat::participantsToString(){
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return std::string();
}
}

