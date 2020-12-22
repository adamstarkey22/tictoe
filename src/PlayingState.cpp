#include "PlayingState.hpp"

#include "GameServer.hpp"
#include <string>
#include <iostream>

PlayingState::PlayingState(GameStateManager* game, bool isHost) : GameState(game)
{
	this->isHost = isHost;
	
	font.loadFromFile("res/belligerent.ttf");
	texture.loadFromFile("res/spritesheet-hdpi.png");
	
	text.setFont(font);
	text.setCharacterSize(25);
	text.setPosition(25, 25);
	text.setFillColor(sf::Color::Black);
	
	restartButton.setFont(font);
	restartButton.setCharacterSize(25);
	restartButton.setPosition(25, 75);
	restartButton.setFillColor(sf::Color::Black);
	restartButton.setString("> Restart match");
	
	quitButton.setFont(font);
	quitButton.setCharacterSize(25);
	quitButton.setPosition(25, 100);
	quitButton.setFillColor(sf::Color::Black);
	quitButton.setString("> Quit to menu");
	
	background.setTexture(texture);
	cross.setTexture(texture);
	naught.setTexture(texture);
	ghostCross.setTexture(texture);
	ghostNaught.setTexture(texture);
	
	background.setTextureRect(sf::IntRect(400, 0, 400, 400));
	cross.setTextureRect(sf::IntRect(0, 0, 200, 200));
	naught.setTextureRect(sf::IntRect(0, 200, 200, 200));
	ghostCross.setTextureRect(sf::IntRect(200, 0, 200, 200));
	ghostNaught.setTextureRect(sf::IntRect(200, 200, 200, 200));

	background.setColor(sf::Color::Black);
	ghostCross.setColor(sf::Color::Black);
	ghostNaught.setColor(sf::Color::Black);
	cross.setColor(sf::Color::Red);
	naught.setColor(sf::Color::Blue);

	background.setPosition(200.0f, 100.0f);
}

void PlayingState::init()
{
	if(isHost) server.init();
	client.init();
}

void PlayingState::destroy()
{
	client.destroy();
	if (isHost) server.destroy();
}

void PlayingState::handleEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (activeTile != -1) {
				sf::Packet packet;
				logic.takeTurn(client.playerId, activeTile);
				packet << GameServer::SERVER_TAKE_TURN << client.playerId << activeTile;
				client.send(packet);
			}
		}
	}
}

void PlayingState::update(sf::RenderWindow* window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	
	if (background.getGlobalBounds().contains(mouse.x, mouse.y)) {
		int tileX = (mouse.x < background.getGlobalBounds().left + background.getGlobalBounds().width / 2) ? 0 : 1;
		int tileY = (mouse.y < background.getGlobalBounds().top + background.getGlobalBounds().height / 2) ? 0 : 1;
		activeTile = tileX + tileY * 2;
	} else {
		activeTile = -1;
	}
}

void PlayingState::render(sf::RenderWindow* window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	
	std::string status;
	
	if (client.logic.currentMatchState == client.logic.MATCH_IN_PROGRESS) {
		if (client.playerId == client.logic.currentPlayer) status = "Your turn";
		else status = "Waiting for other player";
	} else {
		if (client.playerId == client.logic.currentPlayer) status = "You win!";
		else status = "You lose!";
	}

	text.setString(status);

	if (restartButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
		restartButton.setStyle(sf::Text::Underlined);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Packet packet;
			packet << GameServer::SERVER_RESET_MATCH;
			client.send(packet);
		}
	} else {
		restartButton.setStyle(sf::Text::Regular);
	}

	if (quitButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
		quitButton.setStyle(sf::Text::Underlined);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			game->popState();
			return;
		}
	} else {
		quitButton.setStyle(sf::Text::Regular);
	}

	window->draw(background);
	window->draw(text);
	window->draw(restartButton);
	window->draw(quitButton);
	
	for (int i = 0; i < 4; i++) {
		int tileX = background.getGlobalBounds().left + i % 2 * background.getGlobalBounds().width / 2;
		int tileY = background.getGlobalBounds().top + i / 2 * background.getGlobalBounds().height / 2;
		
		switch (client.logic.tiles[i]) {
			case client.logic.PLAYER_CROSS:
				cross.setPosition(tileX, tileY);
				window->draw(cross);
				break;
			case client.logic.PLAYER_NAUGHT:
				naught.setPosition(tileX, tileY);
				window->draw(naught);
				break;
			default:
				if (activeTile == i && client.logic.currentMatchState == client.logic.MATCH_IN_PROGRESS && client.logic.currentPlayer == client.playerId) {					
					switch (client.playerId) {
						case client.logic.PLAYER_CROSS:
							ghostCross.setPosition(tileX, tileY);
							window->draw(ghostCross);
							break;
						case client.logic.PLAYER_NAUGHT:
							ghostNaught.setPosition(tileX, tileY);
							window->draw(ghostNaught);
							break;
					}
				}
		}

	}
}
