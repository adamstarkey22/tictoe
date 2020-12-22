#pragma once

#include "GameLogic.hpp"
#include <SFML/Network.hpp>
#include <thread>

class GameServer {
public:
	static const int SERVER_TAKE_TURN   = 0;
	static const int SERVER_RESET_MATCH = 1;
	static const int CLIENT_SYNC        = 2;
	static const int CLIENT_ASSIGN_ID   = 3;
	
	bool running;
	
	GameServer();
	
	void init();
	void destroy();
private:
	GameLogic logic;
	sf::TcpListener listener;
	sf::TcpSocket clients[2];
	sf::SocketSelector selector;
	std::thread thread;
	
	static void start(GameServer* server);
	void run();
	void sendToAll(sf::Packet packet);
};
