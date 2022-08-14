#pragma once
#include "Types.h"
#include <string>

class BattleField;
class Grid;

using namespace std;

class Character
{
public:
// Constructor
    Character(Types::CharacterClass characterClass, string characterName, int playerIndex, char icon);
    ~Character();

// Settings
    Types::CharacterClass CharacterClass;
    string CharacterName;
    float Health;
    float BaseDamage;
    float DamageMultiplier;
    int PlayerIndex;

// Logic
    int SpecialUses;
    Character* target;
    bool bSuperDefense;
    bool bSuperDamage;
    bool IsDead;
    char Icon;
    Types::GridBox* CurrentBox;

// Functions
    string GetClassEnumAsString(Types::CharacterClass characterClass);

// Methods
    void TakeDamage(Character* attacker, float amount);

    void Die();

    void WalkTo(BattleField* battlefieldReference, int direction);

    void StartTurn(BattleField* battlefield);

    bool CheckCloseTargets(BattleField* battlefield);

    void Attack(Character* target);

    void ClearCurrentGrid();

    void SuperDefense();

    void CancelSuperDefense();

    void SuperDamage();

    void CancelSuperDamage();
};

