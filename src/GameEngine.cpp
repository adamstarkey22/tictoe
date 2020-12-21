#include "GameEngine.hpp"

#include <SFML/Graphics.hpp>
#include "GameStateManager.hpp"

GameEngine::GameEngine()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Toe");
	GameStateManager gameStateManager;
	
	sf::Clock clock;
	sf::Time lag;
	sf::Time delta = sf::seconds(1.0f/60.0f);

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		lag += elapsed;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			gameStateManager.handleEvents(event);
			gameStateManager.update(&window);
			window.clear(sf::Color::White);
			gameStateManager.render(&window);
			window.display();
		}
/*
		while (lag >= delta)
		{
			lag -= delta;
			gameStateManager.update(&window);
		}

		window.clear(sf::Color::White);
		gameStateManager.render(&window);
		window.display();
*/
	}
}
