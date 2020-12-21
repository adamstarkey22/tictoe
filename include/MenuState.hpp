#pragma once

#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class MenuState : public GameState {
public:
	MenuState(GameStateManager* game);
	void init();
	void handleEvents(sf::Event event);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
private:
	std::string username = "";
	bool isMousePressed;
	bool wasMouseDown;
	sf::Font font;
	sf::Text title;
	sf::Text playButton;
};
