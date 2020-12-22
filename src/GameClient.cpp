#include "GameClient.hpp"

#include <iostream>
#include "GameServer.hpp"

GameClient::GameClient() {}

void GameClient::init() {
	logic.reset();

	std::cout << "[CLIENT] Attempting to connect to server" << std::endl;
	
	if (socket.connect("localhost", 53000) != sf::Socket::Done) {
		std::cout << "[CLIENT] Failed to connect to server" << std::endl;
		return;
	}
	
	sf::Packet packet;
	int request;
	int id;
	socket.receive(packet);
	packet >> request >> id;
	//playerId = id;
	playerId = 1;
	
	std::cout << "[CLIENT] Running client loop in seperate thread" << std::endl;
	thread = std::thread(start, this);
}

void GameClient::destroy()
{
	std::cout << "[CLIENT] Attempting to disconnect socket" << std::endl;
	socket.disconnect();
	
	if (thread.joinable()) {
		std::cout << "[CLIENT] Attempting to join thread" << std::endl;
		thread.join();
	} else {
		std::cout << "[CLIENT] Client thread not currently active" << std::endl;
	}
}

void GameClient::start(GameClient* client) { client->run(); }

void GameClient::run()
{
	while (running) {
		sf::Packet packet;
		if (socket.receive(packet) == sf::Socket::Done) {
			std::cout << "[CLIENT] Successfully received packet from server at IP address " << socket.getRemoteAddress() << std::endl;
		} else if ( socket.receive(packet) == sf::Socket::Disconnected ) {
			std::cout << "[CLIENT] Disconnected from server" << std::endl;
			running = false;
		} else {
			std::cout << "[CLIENT] Error receiving packet from server at IP address " << socket.getRemoteAddress() << std::endl;
			running = false;
		}
		
		int request;
		packet >> request;

		switch (request) {
			case GameServer::CLIENT_SYNC:
				packet >> logic.currentPlayer >> logic.currentMatchState >> logic.tiles[0] >> logic.tiles[1] >> logic.tiles[2] >> logic.tiles[3];
				std::cout << "[CLIENT] UPDATED GAMELOGIC" << std::endl;
				break;
			case GameServer::CLIENT_ASSIGN_ID:
				//packet >> playerId;
				//std::cout << "[CLIENT] Received player id of " << playerId << std::endl;
				break;
		}
	}
}

void GameClient::send(sf::Packet packet)
{
	if (socket.send(packet) == sf::Socket::Done) {
		std::cout << "[CLIENT] Successfully sent packet to server" << std::endl;
	} else {
		std::cout << "[CLIENT] Error sending packet to server" << std::endl;
	}
}
