#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01};
IPAddress ip(192, 168, 1, 10);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(0, 0, 0, 0);
IPAddress serverIP(192, 168, 1, 20);
const int PORT = 5000;
const int SW_PIN = 6;
EthernetClient client;
bool ledState = false;
bool lastBtn  = HIGH;
bool connected = false;
void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.println("=== Arduino #1 (Shield / Switch) ===");
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  delay(2000);
  Serial.print("Local IP:    "); Serial.println(Ethernet.localIP());
  Serial.print("Link status: "); Serial.println(Ethernet.linkStatus());
}
void reconnect() {
  client.stop();
  delay(500);
  Serial.println("Connecting to server...");
  if (client.connect(serverIP, PORT)) {
    connected = true;
    Serial.println("Connected!");
  } else {
    Serial.println("Connection failed, retrying in 2s");
    delay(2000);
  }
}
void loop() {
  if (!connected || !client.connected()) {
    connected = false;
    client.stop();
    reconnect();
    return;
  }
  bool btnNow = digitalRead(SW_PIN);
  if (lastBtn == HIGH && btnNow == LOW) {
    ledState = !ledState;
    client.print(ledState ? "ON" : "OFF");
    Serial.print("Sent: ");
    Serial.println(ledState ? "ON" : "OFF");
    delay(50);
  }
  lastBtn = btnNow;
}
