#ifndef NETWORK_HEADER
#define NETWORK_HEADER

#include <Arduino.h>
#include <WiFi.h>

class Network {
    public: 
		void begin(char* network, char* password);
		bool connected();
		void connect();

    private:
		char* network;
		char* password;

		bool attemptConnection();
};

#endif