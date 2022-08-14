#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <string>


using namespace std;

BattleField::BattleField()
{
    // Set the seed for the random generator
    srand((unsigned)time(NULL));

    // Create world, spawn characters, populate world and set the start menu
    Setup();
}

void BattleField::Setup()
{
    // BattleField options and creation
    GetBattlefieldChoice();

    // Player character options and creation
    GetPlayerChoice();

    // Random enemy generator
    CreateEnemyCharacter();

    // World creation and population and the start menu
    StartGame();
}

void BattleField::GetBattlefieldChoice()
{
    // Local variables
    int _xLength;
    int _yLength;

    // Clear console and get the BattleField vertical size
    system("cls");
    cout << "Select the vertical size of the BattleField:\n";
    cin >> _xLength;

    // Exception treatment in case of not number
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        return GetBattlefieldChoice();
    }

    // Make the BattleField not less than 2x2
    if (_xLength < 2)
    {
        _xLength = 2;
    }

    // Clear console and get the BattleField horizontal size
    system("cls");
    cout << "Select the horizontal size of the BattleField:\n";
    cin >> _yLength;

    // Exception treatment in case of not number
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        return GetBattlefieldChoice();
    }

    // Make the BattleField not less than 2x2
    if (_yLength < 2)
    {
        _yLength = 2;
    }

    // Clear console and instantiate and set a new Grid object
    system("cls");
    BattleFieldGrid = new Grid(_xLength, _yLength);
    return;
}

void BattleField::GetPlayerChoice()
{
    // Local variables
    Types::CharacterClass _SelectedClass = Types::Archer;  
    string _CharacterName;
    string _Choice;

    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");
    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");

    // Clear cin history
    cin.clear();
    cin.ignore();

    //store the player choice in a variable
    cin >> _Choice;
    
    // Clear the console
    system("cls");

    // Changed the switch structure to a if alignment
    if (_Choice == "1")
    {
        _SelectedClass = Types::CharacterClass::Paladin;
    }
    else if (_Choice == "2")
    {
        _SelectedClass = Types::CharacterClass::Warrior;
    }
    else if (_Choice == "3")
    {
        _SelectedClass = Types::CharacterClass::Cleric;
    }
    else if (_Choice == "4")
    {
        _SelectedClass = Types::CharacterClass::Archer;
    }
    else
    {
        // Exception treatment in case of a index not valid
        printf("Choose a correct class index!\n\n");
        return GetPlayerChoice();
    }

    // Clear the console
    system("cls");

    // Asks for the character name
    printf("Choose your character name:\n");

    // Clear cin history
    cin.clear();
    cin.ignore();

    //store the player choice in a variable
    cin >> _CharacterName;
    
    // Clear the console
    system("cls");

    // Create a player character
    return CreatePlayerCharacter(_SelectedClass, _CharacterName);
}

void BattleField::CreatePlayerCharacter(Types::CharacterClass characterClass, string characterName)
{
    // Instantiate and set a Character object
    PlayerCharacter = new Character(characterClass, characterName, 0, 'P');

    // Instiantiate feedback
    cout << "Player Character Name: " << characterName << "\nCharacter Class Choice: " << PlayerCharacter->GetClassEnumAsString(characterClass) << "\n\n";
    return;
}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    Types::CharacterClass enemyClass = (Types::CharacterClass)GetRandomInt(1, 4);

    // Instantiate and set a Enemy Character object
    EnemyCharacter = new Character(enemyClass, "Enemy", 1, 'E');

    // Instantiate feedback
    cout << "Enemy Class Choice: " << EnemyCharacter->GetClassEnumAsString(enemyClass) << "\n\n";
    return;
}

void BattleField::StartGame()
{
    // Wait for a press/click to start the game
    system("pause");

    // Clear console
    system("cls");

    //populates the character variables and targets
    EnemyCharacter->target = PlayerCharacter;
    PlayerCharacter->target = EnemyCharacter;
    
    AllPlayers.push_back(PlayerCharacter);
    AllPlayers.push_back(EnemyCharacter);

    // Define the character random positions
    AlocatePlayers();

    // Start character turns
    StartTurn();
}

void BattleField::StartTurn() {

    if (CurrentTurn == 0)
    {
        AllPlayers.sort();  
    }

    auto _TurnCharacter = AllPlayers.begin();

    if (CurrentTurn % 2 == 0)
    {
        Character* _Character = *_TurnCharacter;
        _Character->StartTurn(this);
    }
    else
    {
        advance(_TurnCharacter, 1);
        Character* _Character = *_TurnCharacter;
        _Character->StartTurn(this);
    }

    CurrentTurn++;

    return HandleTurn();
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->Health <= 0)
    {
        BattleOver = true;
        return EnemyCharacterWins();
    }
    else if (EnemyCharacter->Health <= 0)
    {
        BattleOver = true;
        return PlayerCharacterWins();
    }

    return StartTurn();
}

void BattleField::PlayerCharacterWins()
{
    cout << "\n" << PlayerCharacter->CharacterName << " team wins the battle.\n\n";

    system("pause");

    ChoiceRestartGame();
}

void BattleField::EnemyCharacterWins()
{
    cout << "\n" << EnemyCharacter->CharacterName << " team wins the battle.\n\n";

    system("pause");

    ChoiceRestartGame();
}

void BattleField::ChoiceRestartGame()
{
    string _Choice;

    system("cls");

    cout << "Want to restart the game?\n[Y] - Yes.\n[N] - No.\n\n";

    std::getline(std::cin, _Choice);

    if (_Choice == "Y" || _Choice == "y")
    {
        system("cls");

        return RestartGame();
    }
    else if (_Choice == "N" || _Choice == "n")
    {
        system("cls");
        cout << "Thank you for playing the Kokky auto-battle test.";
        exit(0);
    }
    else
    {
        ChoiceRestartGame();
    }
}

void BattleField::RestartGame()
{
    BattleOver = false;
    CurrentTurn = 0;
    AllPlayers.clear();
    PlayerCharacter->~Character();
    EnemyCharacter->~Character();
    BattleFieldGrid->~Grid();

    Setup();
}

int BattleField::GetRandomInt(int min, int max)
{
    // Define the lower and higher value
    int lowerValue = min > max ? max : min;
    int higherValue = max > min ? max : min;

    // Get random value between the lower and higher value
    int random = lowerValue + (rand() % higherValue);

    // Return the random value
    return random;
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();
    AlocateEnemyCharacter();
}

void BattleField::AlocatePlayerCharacter()
{
    int random = GetRandomInt(0, BattleFieldGrid->grids.size() - 1);
    Types::GridBox* RandomLocation = BattleFieldGrid->grids[random];

    if (!RandomLocation->CharacterReference)
    {
        RandomLocation->CharacterReference = PlayerCharacter;
        PlayerCurrentLocation = RandomLocation;
        PlayerCharacter->CurrentBox = RandomLocation;
        BattleFieldGrid->updateBattlefield();
        return;
    }
    else
    {
        return AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    int random = GetRandomInt(0, BattleFieldGrid->grids.size() - 1);
    Types::GridBox* RandomLocation = BattleFieldGrid->grids[random];
    
    if (!RandomLocation->CharacterReference)
    {
        RandomLocation->CharacterReference = EnemyCharacter;
        EnemyCurrentLocation = RandomLocation;
        EnemyCharacter->CurrentBox = RandomLocation;
        BattleFieldGrid->updateBattlefield();
        return;
    }
    else
    {
        return AlocateEnemyCharacter();
    }
}