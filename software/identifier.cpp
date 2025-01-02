#include <Arduino.h>
#include <WiFi.h>

#include "identifier.hpp"

Identifier::Identifier() {
	byte byteA, byteB, byteC;

	uint8_t mac[6];
	WiFi.macAddress(mac);

	byteA = mac[3];
	byteB = mac[4];
	byteC = mac[5];

	name = String("etherrail-power-module-");

	for (char byteIndex = 0; byteIndex < 6; byteIndex++) {
		String byte = String(mac[byteIndex], HEX);

		if (byte.length() == 1) {
			byte = "0" + byte;
		}

		name += byte;
	}
};