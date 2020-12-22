#include "GameServer.hpp"

#include <iostream>

GameServer::GameServer() {}

void GameServer::init()
{
	logic.reset();
	std::cout << "[SERVER] Starting server" << std::endl;
	
	if (listener.listen(53000) != sf::Socket::Done)
	{
		std::cout << "[SERVER] Error initialising TCP listener" << std::endl;
		return;
	}
	
	std::cout << "[SERVER] Initialised TCP listener" << std::endl;
	std::cout << "[SERVER] Running server loop in seperate thread" << std::endl;
	
	thread = std::thread(start, this);
}

void GameServer::destroy()
{
	std::cout << "[SERVER] Attempting to close TCP listener" << std::endl;
	listener.close();
	
	if (thread.joinable()) {
		std::cout << "[SERVER] Attempting to join thread" << std::endl;
		thread.join();
	} else {
		std::cout << "[SERVER] Server thread not currently active" << std::endl;
	}
}

void GameServer::start(GameServer* server) { server->run(); }

void GameServer::run()
{
	for (int i = 0; i < 2; i++) {
		std::cout << "[SERVER] Waiting for " << 2-i << " clients to join" << std::endl;
	
		if (listener.accept(clients[i]) != sf::Socket::Done) {
			std::cout << "[SERVER] Error accepting connection request from client" << std::endl;
			return;
		}

		sf::Packet packet;
		packet << CLIENT_ASSIGN_ID << i + 1;
		if (clients[i].send(packet) == sf::Socket::Done) {
			std::cout << "[SERVER] Assigned playerId of " << i + 1 << " to client " << i << std::endl;
		} else {
			std::cout << "[SERVER] Failed to assign playerId to client " << i << std::endl;
		}
		
		selector.add(clients[i]);
	}
	
	std::cout << "[SERVER] Clients have successfully joined" << std::endl;
	
	running = true;
	while (running) {
		if (selector.wait(sf::seconds(10.0f))) {
			for (int i = 0; i < 2; i++) {
				if (selector.isReady(clients[i])) {
					sf::Packet packet;
					
					if (clients[i].receive(packet) == sf::Socket::Done) {
						std::cout << "[SERVER] Successfully received packet from client " << i <<  " at IP address " << clients[i].getRemoteAddress() << std::endl;
					} else if ( clients[i].receive(packet) == sf::Socket::Disconnected ) {
						std::cout << "[SERVER] Client " << i << " has disconnected" << std::endl;
						running = false;
					} else {
						std::cout << "[SERVER] Error receiving packet from client " << i << " at IP address " << clients[i].getRemoteAddress() << std::endl;
					}
					
					int request;
					packet >> request;
					sf::Packet response;
					
					switch (request) {
						case SERVER_TAKE_TURN:
							int player;
							int tile;
							packet >> player >> tile;
							logic.takeTurn(player, tile);
							response << CLIENT_SYNC << logic.currentPlayer << logic.currentMatchState << logic.tiles[0] << logic.tiles[1] << logic.tiles[2] << logic.tiles[3];
							sendToAll(response);
							break;
						case SERVER_RESET_MATCH:
							logic.reset();
							response << CLIENT_SYNC << logic.currentPlayer << logic.currentMatchState << logic.tiles[0] << logic.tiles[1] << logic.tiles[2] << logic.tiles[3];
							sendToAll(response);
							break;
					}
				}
			}
		}
	}
}

void GameServer::sendToAll(sf::Packet packet)
{
	for (int i = 0; i < 2; i++) {
		if (clients[i].send(packet) == sf::Socket::Done) {
			std::cout << "[SERVER] Successfully sent packet to client " << i << std::endl;
		} else {
			std::cout << "[SERVER] Error sending packet to client " << i << std::endl;
		}
	}
}
