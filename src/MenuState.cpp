#include "MenuState.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayingState.hpp"
#include "GameLogic.hpp"

MenuState::MenuState(GameStateManager* game) : GameState(game)
{
	font.loadFromFile("res/belligerent.ttf");
	
	title.setFont(font);
	title.setCharacterSize(50);
	title.setPosition(25, 25);
	title.setString("Tic Toe");
	title.setFillColor(sf::Color::Black);
	
	hostButton.setFont(font);
	hostButton.setString("> Host a match");
	hostButton.setCharacterSize(25);
	hostButton.setPosition(25, 100);
	hostButton.setFillColor(sf::Color::Black);
	
	joinButton.setFont(font);
	joinButton.setString("> Join a match");
	joinButton.setCharacterSize(25);
	joinButton.setPosition(25, 125);
	joinButton.setFillColor(sf::Color::Black);
}

void MenuState::init() {}

void MenuState::destroy() {}

void MenuState::handleEvents(sf::Event event)
{
}

void MenuState::update(sf::RenderWindow* window)
{
	bool isMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	isMousePressed = isMouseDown && !wasMouseDown;
	wasMouseDown = isMouseDown;
}

void MenuState::render(sf::RenderWindow* window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	
	if (hostButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
		hostButton.setStyle(sf::Text::Underlined);
		if (isMousePressed) {		
			game->pushState(std::make_shared<PlayingState>(game, true));
		}
	} else {
		hostButton.setStyle(sf::Text::Regular);
	}
	
	if (joinButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
		joinButton.setStyle(sf::Text::Underlined);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			game->pushState(std::make_shared<PlayingState>(game, false));
		}
	} else {
		joinButton.setStyle(sf::Text::Regular);
	}
	
	window->draw(hostButton);
	window->draw(joinButton);
	window->draw(title);
}
