#pragma once

#include "GameServer.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class GameState;

class GameStateManager {
public:
	GameStateManager();

	void changeState(std::shared_ptr<GameState> state);
	void pushState(std::shared_ptr<GameState> state);
	void popState();
	
	void handleEvents(sf::Event event);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
private:
	std::vector<std::shared_ptr<GameState>> states;
};
