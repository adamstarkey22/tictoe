#pragma once

#include "GameState.hpp"
#include "GameLogic.hpp"
#include "GameClient.hpp"
#include "GameServer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>

class PlayingState : public GameState {
public:
	PlayingState(GameStateManager* game, bool isHost);
	
	void init();
	void destroy();
	
	void handleEvents(sf::Event event);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
private:
	int activeTile;
	GameLogic logic;
	
	bool isHost;
	GameServer server;
	GameClient client;

	sf::Texture texture;
	sf::Sprite background;
	sf::Sprite cross;
	sf::Sprite naught;
	sf::Sprite ghostCross;
	sf::Sprite ghostNaught;
	sf::Font font;
	sf::Text text;
	sf::Text restartButton;
	sf::Text quitButton;
};
