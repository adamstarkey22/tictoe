#include "MenuState.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayingState.hpp"

MenuState::MenuState(GameStateManager* game) : GameState(game)
{
	font.loadFromFile("res/belligerent.ttf");
	
	title.setFont(font);
	title.setCharacterSize(50);
	title.setPosition(25, 25);
	title.setString("Tic Toe");
	title.setFillColor(sf::Color::Black);
	
	playButton.setFont(font);
	playButton.setString("> Play on this device");
	playButton.setCharacterSize(25);
	playButton.setPosition(25, 100);
	playButton.setFillColor(sf::Color::Black);
}

void MenuState::init()
{}

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
	if (playButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
		playButton.setStyle(sf::Text::Underlined);
		if (isMousePressed) game->pushState(std::make_shared<PlayingState>(game));
	} else {
		playButton.setStyle(sf::Text::Regular);
	}

	window->draw(playButton);
	window->draw(title);
}
