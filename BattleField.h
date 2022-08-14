#pragma once
#include "Types.h"
#include <list>
#include <iostream>
#include <string>

class Character;
class Grid;

using namespace std;

class BattleField
{
public:

// Constructor
	BattleField();

// Logic
	Grid* BattleFieldGrid;

	Types::GridBox* PlayerCurrentLocation;
	Types::GridBox* EnemyCurrentLocation;

	list<Character*> AllPlayers;

	Character* PlayerCharacter;
	Character* EnemyCharacter;

	int CurrentTurn;
	bool BattleOver;

// Functions
	int GetRandomInt(int min, int max);

// Methods
	void Setup();

	void GetBattlefieldChoice();

	void GetPlayerChoice();

	void CreatePlayerCharacter(Types::CharacterClass characterClass, string characterName);

	void CreateEnemyCharacter();

	void AlocatePlayers();

	void AlocatePlayerCharacter();

	void AlocateEnemyCharacter();

	void StartGame();

	void StartTurn();

	void HandleTurn();

	void PlayerCharacterWins();

	void EnemyCharacterWins();

	void ChoiceRestartGame();

	void RestartGame();
};


