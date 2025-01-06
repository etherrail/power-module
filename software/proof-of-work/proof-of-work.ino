/*
 Web client
 
 This sketch connects to a test website (httpbin.org)
 and try to do a GET request, the output is printed
 on Serial
 
 by Renzo Mischianti <www.mischianti.org>
 
 https://www.mischianti.org
 
 */
 
#include <SPI.h>
#include <Ethernet.h>
 
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)
char server[] = "httpbin.org";    // name address for Google (using DNS)
 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
 
// Set the static IP address to use if the DHCP fails to assign
#define MYIPADDR 192,168,1,28
#define MYIPMASK 255,255,255,0
#define MYDNS 192,168,1,1
#define MYGW 192,168,1,1
 
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
 
// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement
 
#define TRACK_POWER_ENABLE_PIN 20
#define TRACK_DIRECTION_PIN 21

void setup() {
	pinMode(TRACK_POWER_ENABLE_PIN, OUTPUT);
	pinMode(TRACK_DIRECTION_PIN, OUTPUT);

	digitalWrite(TRACK_POWER_ENABLE_PIN, LOW);
	digitalWrite(TRACK_DIRECTION_PIN, LOW);

    Serial.begin(115200);
    delay(1000);
    Serial.println("Begin Ethernet");
 
    // You can use Ethernet.init(pin) to configure the CS pin
    //Ethernet.init(10);  // Most Arduino shields
	// SPI.begin(6, 2, 7, 10);

	Serial.print("SCK"); Serial.println(SCK);
	Serial.print("MISO"); Serial.println(MISO);
	Serial.print("MOSI"); Serial.println(MOSI);
	Serial.print("SS"); Serial.println(SS);

    Ethernet.init(7);   // MKR ETH Shield
    //Ethernet.init(0);   // Teensy 2.0
    //Ethernet.init(20);  // Teensy++ 2.0
    //Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
    //Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet
 
    if (Ethernet.begin(mac)) { // Dynamic IP setup
        Serial.println("DHCP OK!");
    }else{
        Serial.println("Failed to configure Ethernet using DHCP");
        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
          Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
          while (true) {
            delay(1); // do nothing, no point running without Ethernet hardware
          }
        }
        if (Ethernet.linkStatus() == LinkOFF) {
          Serial.println("Ethernet cable is not connected.");
        }
 
          IPAddress ip(MYIPADDR);
          IPAddress dns(MYDNS);
          IPAddress gw(MYGW);
          IPAddress sn(MYIPMASK);
          Ethernet.begin(mac, ip, dns, gw, sn);
          Serial.println("STATIC OK!");
    }
    delay(5000);
 
 
    Serial.print("Local IP : ");
    Serial.println(Ethernet.localIP());
    Serial.print("Subnet Mask : ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("Gateway IP : ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("DNS Server : ");
    Serial.println(Ethernet.dnsServerIP());
 
   Serial.println("Ethernet Successfully Initialized");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("Connected!");
    // Make a HTTP request:
    client.println("GET /get HTTP/1.1");
    client.println("Host: httpbin.org");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
}
 
void loop() {
	Serial.println(Ethernet.hardwareStatus());
	
	digitalWrite(TRACK_POWER_ENABLE_PIN, HIGH);
	delay(500);

	digitalWrite(TRACK_DIRECTION_PIN, HIGH);
	delay(500);

	digitalWrite(TRACK_POWER_ENABLE_PIN, LOW);
	delay(500);

	digitalWrite(TRACK_DIRECTION_PIN, LOW);
	delay(500);
}