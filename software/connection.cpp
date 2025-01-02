#include <Arduino.h>
#include <WiFi.h>

#include "connection.hpp"
#include "discovery.hpp"
#include "network.hpp"

#define CONNECTION_PORT 141

void Connection::begin(Network _network, ConnectionLoopHandler handler) {
	connectionLoopHandler = handler;
	network = _network;

	Serial.println("connecting to network");

	network.connect();

	Serial.println("creating discovery...");
	Discovery discovery();

	Serial.println("finding host...");
	findHost();

	WiFiClient client();

	// start connecting
	reconnectionAttempts = 0;

	while (true) {
		connect();
	}
};

void Connection::findHost() {
	Serial.println("find host...");

	host = discovery.find();
};

void Connection::connect() {
	client.stop();
	reconnectionAttempts++;

	Serial.println("stopped client");

	// make sure that the network is connected
	network.connect();

	// search for a host again after 25 failed attempts
	// the old host might have gone down and been replaced by a new host
	// 
	// find the host on the very first attempt too
	if (reconnectionAttempts == 25) {
		reconnectionAttempts = 0;

		findHost();
	}

	Serial.print("connecting to ");
	Serial.println(host);

	if (client.connect(host, CONNECTION_PORT)) {
		reconnectionAttempts = 0;

		Serial.println("connected");

		while (client.connected()) {
			connectionLoopHandler(client);
		}

		Serial.println("disconnected");
	} else {
		Serial.println("retrying connection");
	}
};