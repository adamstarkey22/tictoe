#include "GameStateManager.hpp"

#include "MenuState.hpp"

GameStateManager::GameStateManager()
{
	pushState(std::make_shared<MenuState>(this));
}

void GameStateManager::changeState(std::shared_ptr<GameState> state)
{
	states.back()->destroy();
	states.back() = state;
	states.back()->init();
}

void GameStateManager::pushState(std::shared_ptr<GameState> state)
{
	states.push_back(state);
	states.back()->init();
}

void GameStateManager::popState()
{
	states.back()->destroy();
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
