#pragma once

class GameLogic {
public:
	static const int PLAYER_NONE = 0;
	static const int PLAYER_CROSS = 1;
	static const int PLAYER_NAUGHT = 2;
	
	static const int MATCH_IN_PROGRESS = 0;
	static const int MATCH_OVER = 1;
	
	int currentPlayer;
	int currentMatchState;
	int tiles[4] = {PLAYER_NONE};
	
	GameLogic();
	void reset();
	void takeTurn(int player, int index);
};
