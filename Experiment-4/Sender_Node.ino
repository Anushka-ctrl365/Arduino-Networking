#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x04};
IPAddress ip(192, 168, 2, 30);        // same subnet as Module B
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(0, 0, 0, 0);
IPAddress bridgeIP(192, 168, 2, 20);  // Module B's IP on Arduino #2
const int PORT = 5001;
const int SW_PIN = 6;
EthernetClient client;
bool ledState  = false;
bool lastBtn   = HIGH;
bool connected = false;
void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP);

  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  delay(2000);
  Serial.print("Arduino #3 IP: "); Serial.println(Ethernet.localIP());
  Serial.print("Link status:   "); Serial.println(Ethernet.linkStatus());
}

void reconnect() {
  client.stop();
  delay(500);
  Serial.println("Connecting to bridge...");
  if (client.connect(bridgeIP, PORT)) {
    connected = true;
    Serial.println("Connected to bridge!");
  } else {
    Serial.println("Failed, retrying in 2s");
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
