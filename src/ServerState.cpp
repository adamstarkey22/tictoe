#include "ServerState.hpp"

#include "PlayingState.hpp"
#include <iostream>

ServerState::ServerState(GameStateManager* game) : GameState(game) {}

void ServerState::init() {
	font.loadFromFile("res/belligerent.ttf");
	
	text.setFont(font);
	text.setCharacterSize(15);
	text.setPosition(25, 25);
	text.setFillColor(sf::Color::Black);
	text.setString("Attempting to run server. Check terminal for status or click here to terminate it safely.");
	
	server.init();
}

void ServerState::destroy() {
	server.destroy();
}

void ServerState::handleEvents(sf::Event event) {}

void ServerState::update(sf::RenderWindow* window) {}

void ServerState::render(sf::RenderWindow* window) {
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	
	if (text.getGlobalBounds().contains(mouse.x, mouse.y)) {
		text.setStyle(sf::Text::Underlined);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			server.running = false;
			game->popState();
			return;
		}
	} else {
		text.setStyle(sf::Text::Regular);
	}
	
	window->draw(text);
}
