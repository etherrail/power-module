#ifndef CONNECTION_HEADER
#define CONNECTION_HEADER

#include "discovery.hpp"
#include "network.hpp"

#include <Arduino.h>
#include <WiFi.h>

using ConnectionLoopHandler = void (*)(WiFiClient);

class Connection {
    public: 
		void begin(Network _network, ConnectionLoopHandler _connectionLoopHandler);

    private:
		IPAddress host;

        WiFiClient client;
		Discovery discovery;
		Network network;

		char reconnectionAttempts;
		ConnectionLoopHandler connectionLoopHandler;

		void findHost();
		void connect();
};

#endif