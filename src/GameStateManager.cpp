#include "GameStateManager.hpp"

#include "MenuState.hpp"

GameStateManager::GameStateManager()
{
	pushState(std::make_shared<MenuState>(this));
}

void GameStateManager::changeState(std::shared_ptr<GameState> state)
{
	states.back() = state;
}

void GameStateManager::pushState(std::shared_ptr<GameState> state)
{
	states.push_back(state);
}

void GameStateManager::popState()
{
	states.pop_back();
}

void GameStateManager::handleEvents(sf::Event event)
{
	states.back()->handleEvents(event);
}

void GameStateManager::update(sf::RenderWindow* window)
{
	states.back()->update(window);
}

void GameStateManager::render(sf::RenderWindow* window)
{
	states.back()->render(window);
}
