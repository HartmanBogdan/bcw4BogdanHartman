#include "VampireState.h"

VampireState::VampireState(Unit* owner) {
    this->ownerunit = owner;
}
VampireState::~VampireState(){}
void VampireState::attack(Unit* enemy){
    if (enemy->GetHP() > 0) {
        enemy->takeAttack(ownerunit);
        enemy->ContAttack(ownerunit);
        int ownerHP = ownerunit->GetMaxHP();
        int drinkHP = ownerunit->GetHP() + (ownerunit->GetPAtk() / 3);
        if (drinkHP < ownerHP){
            ownerunit->SetHp(drinkHP);
        } else if ( drinkHP < ownerHP){
            ownerunit->SetHp(ownerHP);
        } else if (enemy->GetHP() < 20 && enemy->GetHP() > 0){
            ownerunit->bite(enemy);
        }
    } else {
        std::cout << "Can not attack unit, cos it is dead." << std::endl;
    }

}
void VampireState::takeAttack(Unit* enemy){
    int myHP = ownerunit->GetHP();
    if ( myHP > 0 ) {
        int DMG = enemy->GetPAtk();
        if (enemy->GetID() == 6 || enemy->GetID() == 7 || enemy->GetID() == 8 || enemy->GetID() == 9 || enemy->GetID() == 10 ) {
            if (ownerunit->GetID() != 3) {
                DMG += enemy->GetMAtk();
                if (ownerunit->GetID() == 4 && enemy->GetID() == 8){
                    DMG = DMG*2;
                }
            }
        }
        myHP -= DMG;
        if (myHP > 0) {
            ownerunit->SetHp(myHP);
        } else if ( myHP < 0 ) {
            ownerunit->SetHp(0);
            ownerunit->observerble();
            std::cout << enemy->GetName() << " kill " << ownerunit->GetName()<< std::endl;
        }

    } else if ( myHP <= 0 ) {
        std::cout << ownerunit->GetName() << " Is dead."<< std::endl;
    }

}
void VampireState::ContAttack(Unit* enemy){
    if (enemy->GetID() != 2 ) {
        int enemyHP = enemy->GetHP();
        if ( enemyHP > 0 ) {
            int DMG = ownerunit->GetPAtk();
            if (ownerunit->GetID() == 6 || ownerunit->GetID() == 7 || ownerunit->GetID() == 8 || ownerunit->GetID() == 9 || ownerunit->GetID() == 10 ) {
                if ( enemy->GetID() != 3) {
                    DMG += ownerunit->GetMAtk();
                }
            }
            DMG = DMG / 3;
            enemyHP -= DMG;
            if (enemyHP > 0) {
                enemy->SetHp(enemyHP);
            } else if ( enemyHP < 0 ) {
                enemy->SetHp(0);
                enemy->observerble();
                std::cout << ownerunit->GetName() << " kill " << enemy->GetName() << " by conter attack"<< std::endl;
            }
        } else if ( enemyHP <= 0 ) {
            std::cout << enemy->GetName() << " Is dead."<< std::endl;
        }
    } else if (enemy->GetID() == 2 ) {
        std::cout << ownerunit->GetName() << " can not conter attack Rogue."<< std::endl;
    }
}
