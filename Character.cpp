#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"
#include <vector>
#include <algorithm>
#include <string>
#include "BattleField.h"
#include<windows.h>

using namespace std;

Character::Character(Types::CharacterClass characterClass, string characterName, int playerIndex, char icon)
{
    // Set the Character default values
    CharacterClass = characterClass;
    CharacterName = characterName;
    Health = 100.0f;
    BaseDamage = 20.0f;
    DamageMultiplier = 1.0f;
    PlayerIndex = playerIndex;
    Icon = icon;
    SpecialUses = 3;
}

Character::~Character() 
{

}

void Character::TakeDamage(Character* attacker, float amount) 
{
    // Treatment exception: Verify if character is dead
    if (!IsDead)
    {
        // Treatment exception: Verify if character is not on Super Defense special
        if (!bSuperDefense)
        {
            // Remove health by passed amount
            Health -= amount;

            // Verify if health is equal at death (zero)
            if (Health <= 0)
            {
                Die();
            }
            else
            {
                // Damage feedback
                cout << CharacterName << " loses " << amount << " hitpoints due " << attacker->CharacterName << " attack and has " << Health << " hitpoints left.\n\n";
            }
        }
        else
        {
            // Super defense feedback
            cout << CharacterName << " was not damaged due damage reduction.\n\n";
        }
    }
}

void Character::Die() 
{
    // Update status and give feedback
    IsDead = true;
    cout << "\n" << CharacterName << " died in battle.\n";
    Sleep(2000);
	// TODO >> kill
    //TODO >> end the game?
}

void Character::WalkTo(BattleField* battlefieldReference, int direction) 
{
    // 1 = Up
    // 2 = Right
    // 3 = Down
    // 4 = Left

    // Treatment exception
    if (!IsDead && battlefieldReference)
    {
        // Walk to UP
        if (direction == 1)
        {
            if (CurrentBox->xIndex > 0)
            {
                int _GridIndex = CurrentBox->Index - battlefieldReference->BattleFieldGrid->yLength;
                Types::GridBox* _IncomingGridBox = battlefieldReference->BattleFieldGrid->grids[_GridIndex];
                if (_IncomingGridBox->CharacterReference == nullptr)
                {
                    _IncomingGridBox->CharacterReference = this;
                    ClearCurrentGrid();
                    CurrentBox = _IncomingGridBox;
                    battlefieldReference->BattleFieldGrid->updateBattlefield();
                }
            }
        }
        // Walk to RIGHT
        else if (direction == 2)
        {
            if (CurrentBox->yIndex < battlefieldReference->BattleFieldGrid->yLength)
            {
                int _GridIndex = CurrentBox->Index + 1;
                Types::GridBox* _IncomingGridBox = battlefieldReference->BattleFieldGrid->grids[_GridIndex];
                if (_IncomingGridBox->CharacterReference == nullptr)
                {
                    _IncomingGridBox->CharacterReference = this;
                    ClearCurrentGrid();
                    CurrentBox = _IncomingGridBox;
                    battlefieldReference->BattleFieldGrid->updateBattlefield();
                }
            }
        }
        // Walk to DOWN
        else if (direction == 3)
        {
            if (CurrentBox->xIndex < battlefieldReference->BattleFieldGrid->xLength)
            {
                int _GridIndex = CurrentBox->Index + battlefieldReference->BattleFieldGrid->yLength;
                Types::GridBox* _IncomingGridBox = battlefieldReference->BattleFieldGrid->grids[_GridIndex];
                if (_IncomingGridBox->CharacterReference == nullptr)
                {
                    _IncomingGridBox->CharacterReference = this;
                    ClearCurrentGrid();
                    CurrentBox = _IncomingGridBox;
                    battlefieldReference->BattleFieldGrid->updateBattlefield();
                }
            }
        }
        // Walk to LEFT
        else if (direction == 4)
        {
            if (CurrentBox->yIndex > 0)
            {
                int _GridIndex = CurrentBox->Index - 1;
                Types::GridBox* _IncomingGridBox = battlefieldReference->BattleFieldGrid->grids[_GridIndex];
                if (_IncomingGridBox->CharacterReference == nullptr)
                {
                    _IncomingGridBox->CharacterReference = this;
                    ClearCurrentGrid();
                    CurrentBox = _IncomingGridBox;
                    battlefieldReference->BattleFieldGrid->updateBattlefield();
                }
            }
        }
    }
}

void Character::StartTurn(BattleField* battlefield)
{
    if (!IsDead && battlefield)
    {
        // A delay between turns.
        Sleep(1750);

        // Verify if there's targets close
        if (CheckCloseTargets(battlefield))
        {
            // Cancel specials if is activated
            if (bSuperDamage)
            {
                CancelSuperDamage();
           }

            if (bSuperDefense)
            {
                CancelSuperDefense();
            }

            // Try to activate specials
            int _DefenseChance = battlefield->GetRandomInt(0, 100);
            if (Health < _DefenseChance && SpecialUses > 0)
            {
                SuperDefense();
            }

            int _DamageChance = battlefield->GetRandomInt(0, 100);
            if (Health > _DamageChance)
            {
                SuperDamage();
            }

            // Attack the target
            Attack(target);
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
            if (CurrentBox->xIndex > target->CurrentBox->xIndex)
            {
                WalkTo(battlefield, 1);
                cout << CharacterName << " moves up.\n\n";
            }
            else if (CurrentBox->xIndex < target->CurrentBox->xIndex)
            {
                WalkTo(battlefield, 3);
                cout << CharacterName << " moves down.\n\n";
            }
            else if (CurrentBox->yIndex > target->CurrentBox->yIndex)
            {
                WalkTo(battlefield, 4);
                cout << CharacterName << " moves left.\n\n";
            }
            else if (CurrentBox->yIndex < target->CurrentBox->yIndex)
            {
                WalkTo(battlefield, 2);
                cout << CharacterName << " moves right.\n\n";
            }
        }
    }
    return;
}

bool Character::CheckCloseTargets(BattleField* battlefield)
{
    int _xDistance = CurrentBox->xIndex - target->CurrentBox->xIndex;
    int _yDistance = CurrentBox->yIndex - target->CurrentBox->yIndex;

    if (_xDistance >= -1 && _xDistance <= 1 && _yDistance >= -1 && _yDistance <= 1)
    {
        return true;
    }

    return false;
}

void Character::Attack(Character* target) 
{
    if (!IsDead)
    {
        float _HitDamage = BaseDamage * DamageMultiplier;

        cout << CharacterName << " attacked " << target->CharacterName << " for " << _HitDamage << " hitpoints.\n";

        target->TakeDamage(this, _HitDamage);
    }
}

string Character::GetClassEnumAsString(Types::CharacterClass characterClass)
{
    if (characterClass == Types::CharacterClass::Archer)
    {
        return "Archer";
    }
    else if (characterClass == Types::CharacterClass::Cleric)
    {
        return "Cleric";
    }
    else if (characterClass == Types::CharacterClass::Paladin)
    {
        return "Paladin";
    }
    else if (characterClass == Types::CharacterClass::Warrior)
    {
        return "Warrior";
    }
    else
    {
        return "No Class";
    }
}

void Character::ClearCurrentGrid()
{
    if (CurrentBox)
    {
        CurrentBox->CharacterReference = nullptr;
        CurrentBox = nullptr;
    }
}

void Character::SuperDamage()
{
    if (SpecialUses > 0)
    {
        SpecialUses--;

        cout << CharacterName << " uses the Super Damage special.\n";
        Sleep(1000);

        DamageMultiplier += 1;
        bSuperDamage = true;
    }
}

void Character::CancelSuperDamage()
{
    if (bSuperDamage)
    {
        cout << CharacterName << " loses the Super Damage special effect.\n";
        Sleep(1000);
        
        DamageMultiplier -= 1;
        bSuperDamage = false;
    }
}

void Character::SuperDefense()
{
    if (SpecialUses > 0)
    {
        SpecialUses--;

        cout  <<CharacterName << " uses the Super Defense special.\n";
        Sleep(1000);

        bSuperDefense = true;
    }
}

void Character::CancelSuperDefense()
{
    if (bSuperDefense)
    {
        cout << CharacterName << " loses the Super Defense special effect.\n";
        Sleep(1000);

        bSuperDefense = false;
    }
}