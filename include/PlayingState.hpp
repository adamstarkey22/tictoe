#pragma once

#include "GameState.hpp"
#include "GameLogic.hpp"
#include <SFML/Graphics.hpp>

/*namespace sf {
	class RenderWindow;
}*/

class PlayingState : public GameState {
public:
	PlayingState(GameStateManager* game);
	void init();
	void handleEvents(sf::Event event);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
private:
	int activeTile;
	GameLogic logic;
	
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
