#pragma once

#include <SFML/Network.hpp>
#include <thread>
#include "GameLogic.hpp"

class GameClient {
public:
	GameLogic logic;
	int playerId = GameLogic::PLAYER_NONE;
	bool running;
	
	GameClient();
	
	void init();
	void destroy();
	
	void send(sf::Packet packet);
private:
	sf::TcpSocket socket;
	std::thread thread;
	
	static void start(GameClient* client);
	void run();
};
