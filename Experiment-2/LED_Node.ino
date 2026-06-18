#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02};
IPAddress ip(192, 168, 1, 20);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(0, 0, 0, 0);
const int LED_PIN = 5;
const int RST_PIN = 9;
const int CS_PIN  = 10;
const int PORT    = 5000;
EthernetServer server(PORT);
EthernetClient client;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  // Explicitly initialise CS before anything touches SPI
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  // Disable SD card CS (just in case)
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  // Hard reset W5500
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, LOW);
  delay(500);                   // hold reset longer
  digitalWrite(RST_PIN, HIGH);
  delay(1000);                  // give W5500 full boot time
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("=== Arduino #2 (W5500 Module / LED) ===");
  Serial.println("Initialising Ethernet...");
  Ethernet.init(CS_PIN);        // explicitly tell library which CS pin
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  delay(2000);
  Serial.print("Hardware:    ");
  switch (Ethernet.hardwareStatus()) {
    case EthernetNoHardware:
      Serial.println("NO HARDWARE FOUND — check SPI wiring");
      while (true) { delay(1000); }   // stop here, no point continuing
    case EthernetW5100: Serial.println("W5100 detected"); break;
    case EthernetW5200: Serial.println("W5200 detected"); break;
    case EthernetW5500: Serial.println("W5500 detected — correct"); break;
  }
  Serial.print("Local IP:    "); Serial.println(Ethernet.localIP());
  Serial.print("Link status: ");
  switch (Ethernet.linkStatus()) {
    case Unknown:  Serial.println("UNKNOWN"); break;
    case LinkON:   Serial.println("LINK ON"); break;
    case LinkOFF:  Serial.println("LINK OFF — check cable"); break;
  }
  server.begin();
  Serial.println("Server listening on port 5000");
  Serial.println("Waiting for client...");
}
void loop() {
  if (!client || !client.connected()) {
    client = server.available();
    if (client) {
      Serial.println("Client connected!");
    }
  }
  if (client && client.available()) {
    String msg = "";
    while (client.available()) {
      msg += (char)client.read();
    }
    msg.trim();
    Serial.print("Received: "); Serial.println(msg);
    if (msg == "ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    }
    if (msg == "OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }
}
