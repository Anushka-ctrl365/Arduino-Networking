#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01};
IPAddress ip(192, 168, 1, 10);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(0, 0, 0, 0);
const int LED_PIN = 5;
const int PORT    = 5000;
EthernetServer server(PORT);
EthernetClient client;
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  delay(2000);
  Serial.print("Arduino #1 IP: "); Serial.println(Ethernet.localIP());
  Serial.print("Link status:   "); Serial.println(Ethernet.linkStatus());
  server.begin();
  Serial.println("Server listening on port 5000");
}
void loop() {
  if (!client || !client.connected()) {
    client = server.available();
    if (client) Serial.println("Client connected!");
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
