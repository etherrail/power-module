#include "identifier.hpp"
#include "connection.hpp"

#include <SPI.h>
#include <WiFi.h>

#define TRACK_POWER_ENABLE_PIN 7
#define TRACK_DIRECTION_PIN 6

Connection connection;

void setup() {
	Identifier identifier;
	Network network;

	// disable power on startup
	pinMode(TRACK_POWER_ENABLE_PIN, OUTPUT);
	pinMode(TRACK_DIRECTION_PIN, OUTPUT);

	digitalWrite(TRACK_POWER_ENABLE_PIN, LOW);
	digitalWrite(TRACK_DIRECTION_PIN, LOW);

	Serial.begin(115200);
	delay(1500);

	Serial.println("connecting to network");

	// TODO add better initial authentication method
	network.begin("EtherRail", "EtherRail1");

	Serial.println("creating connection");
	connection.begin(network, connectionLoopHandler);
}

void connectionLoopHandler(WiFiClient client) {
	if (client.available()) {
		char command = client.read();

		switch (command) {
			case 'a': {
				digitalWrite(TRACK_POWER_ENABLE_PIN, LOW);

				return;
			}

			case 'A': {
				digitalWrite(TRACK_POWER_ENABLE_PIN, HIGH);

				return;
			}

			case 'b': {
				digitalWrite(TRACK_DIRECTION_PIN, LOW);

				return;
			}

			case 'B': {
				digitalWrite(TRACK_DIRECTION_PIN, HIGH);

				return;
			}
		}
	}
}

void loop() {}
