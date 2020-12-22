#pragma once

#include <memory>
#include "GameStateManager.hpp"

namespace sf {
	class RenderWindow;
	class Event;
}

class GameState {
public:
	virtual void init() = 0;
	virtual void destroy() = 0;
	
	virtual void handleEvents(sf::Event event) = 0;
	virtual void update(sf::RenderWindow* window) = 0;
	virtual void render(sf::RenderWindow* window) = 0;

	void changeState(GameStateManager* game, std::shared_ptr<GameState> state)
	{
		game->changeState(state);
	}
protected:
	GameStateManager* game;
	GameState(GameStateManager* game) {
		this->game = game;
	}
	
};
