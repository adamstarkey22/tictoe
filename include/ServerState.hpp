#pragma once

#include "GameState.hpp"
#include "GameServer.hpp"

class ServerState : public GameState {
public:
	ServerState(GameStateManager* game);
	
	void init();
	void destroy();
	
	void handleEvents(sf::Event event);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
private:
	GameServer server;
	sf::Font font;
	sf::Text text;
};
