#pragma once

#include "GameState.hpp"
#include "GameLogic.hpp"
#include "GameClient.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>

class PlayingState : public GameState {
public:
	PlayingState(GameStateManager* game);
	
	void init();
	void destroy();
	
	void handleEvents(sf::Event event);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
private:
	int activeTile;
	GameLogic logic;
	
	GameClient client;
	
	std::thread serverThread;
	sf::TcpSocket socket;

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
