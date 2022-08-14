#pragma once
#include <string>

class Character;

using namespace std;

class Types
{
public:
    
    // GridBox struct corrections.
    // Removed the "broken" constructor;
    struct GridBox
    {
        int xIndex;
        int yIndex;
        int Index;
        Character* CharacterReference;
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };
};

