#include "GameLogic.hpp"

GameLogic::GameLogic()
{
}

void GameLogic::reset()
{
	currentPlayer = PLAYER_CROSS;
	currentMatchState = MATCH_IN_PROGRESS;
	
	for (int i = 0; i < 4; i++)
	{
		tiles[i] = PLAYER_NONE;
	}
}

void GameLogic::takeTurn(int player, int index)
{
	if (currentMatchState != MATCH_IN_PROGRESS) return;
	if (currentPlayer != player) return;
	if (tiles[index] != PLAYER_NONE) return;
	
	tiles[index] = currentPlayer;
	
	int playerCrossScore = 0;
	int playerNaughtScore = 0;
	
	for (int i = 0; i < 4; i++)
	{
		playerCrossScore += tiles[i] == PLAYER_CROSS ? 1 : 0;
		playerNaughtScore += tiles[i] == PLAYER_NAUGHT ? 1 : 0;
	}
	
	if (playerCrossScore >= 2 || playerNaughtScore >= 2)
	{
		currentMatchState = MATCH_OVER;
	}
	else
	{
		switch (currentPlayer)
		{
			case PLAYER_CROSS:
				currentPlayer = PLAYER_NAUGHT;
				break;
			case PLAYER_NAUGHT:
				currentPlayer = PLAYER_CROSS;
				break;
		}
	}
}
