#include <Arduino.h>
#include <WiFi.h>

#include "network.hpp"

void Network::begin(char* _network, char* _password) {
	network = _network;
	password = _password;
};

bool Network::connected() {
	return WiFi.status() == WL_CONNECTED;
};

void Network::connect() {
	if (connected()) {
		return;
	}

	while (!attemptConnection()) {
		delay(250);
	}
};

bool Network::attemptConnection() {
	Serial.println("connecting to network");

	// reset wifi
	/// WiFi.disconnect(true);
	Serial.println("reset network");

	Serial.print("connecting to ");
	Serial.println(network);

	WiFi.begin(network, password);

	delay(250);

	while (true) {
		switch (WiFi.status()) {
			case WL_CONNECTED: {
				Serial.println("network connected");

				return true;
			}

			case WL_NO_SHIELD: {
				Serial.println("! no wifi module found");

				return false;
			}

			case WL_NO_SSID_AVAIL: {
				Serial.println("! no wifi ssid available");

				return false;
			}

			case WL_CONNECT_FAILED: {
				Serial.println("! connection failed");

				return false;
			}

			case WL_DISCONNECTED: {
				Serial.println("! connection disconnected");

				return false;
			}

			case WL_CONNECTION_LOST: {
				Serial.println("! connection lost");

				return false;
			}
		}

		delay(1);
	}
};