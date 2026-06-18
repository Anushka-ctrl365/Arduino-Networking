#include <SPI.h>
#include <Ethernet.h>
// Module A — faces Arduino #1 (LED side)
byte macA[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02};
IPAddress ipA(192, 168, 1, 20);       // same subnet as Arduino #1
IPAddress serverIP(192, 168, 1, 10);  // Arduino #1's IP
const int CS_A   = 10;
const int RST_A  = 7;
const int PORT_A = 5000;
// Module B — faces Arduino #3 (Switch side)
byte macB[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03};
IPAddress ipB(192, 168, 2, 20);       // different subnet for Module B side
const int CS_B   = 9;
const int RST_B  = 8;
const int PORT_B = 5001;
EthernetClient clientA;               // connects to Arduino #1
EthernetServer serverB(PORT_B);       // listens for Arduino #3
EthernetClient clientB;
bool connectedA = false;
void resetModule(int rstPin, int csPin) {
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);
  pinMode(rstPin, OUTPUT);
  digitalWrite(rstPin, LOW);
  delay(500);
  digitalWrite(rstPin, HIGH);
  delay(1000);
}
void setup() {
  Serial.begin(9600);
  // Disable both CS pins first
  pinMode(CS_A, OUTPUT); digitalWrite(CS_A, HIGH);
  pinMode(CS_B, OUTPUT); digitalWrite(CS_B, HIGH);
  // Reset and init Module A
  resetModule(RST_A, CS_A);
  Ethernet.init(CS_A);
  Ethernet.begin(macA, ipA, IPAddress(0,0,0,0), IPAddress(0,0,0,0), IPAddress(255,255,255,0));
  delay(2000);
  Serial.print("Module A IP: "); Serial.println(Ethernet.localIP());
  Serial.print("Module A Link: "); Serial.println(Ethernet.linkStatus());
  // Reset and init Module B
  resetModule(RST_B, CS_B);
  Ethernet.init(CS_B);
  Ethernet.begin(macB, ipB, IPAddress(0,0,0,0), IPAddress(0,0,0,0), IPAddress(255,255,255,0));
  delay(2000);
  Serial.print("Module B IP: "); Serial.println(Ethernet.localIP());
  Serial.print("Module B Link: "); Serial.println(Ethernet.linkStatus());
  serverB.begin();
  Serial.println("Bridge ready — listening for switch side on port 5001");
}
void reconnectA() {
  Ethernet.init(CS_A);
  clientA.stop();
  delay(500);
  Serial.println("Connecting to Arduino #1...");
  if (clientA.connect(serverIP, PORT_A)) {
    connectedA = true;
    Serial.println("Connected to Arduino #1!");
  } else {
    Serial.println("Failed, retrying in 2s");
    delay(2000);
  }
}
void loop() {
  // Maintain connection to Arduino #1 via Module A
  if (!connectedA || !clientA.connected()) {
    connectedA = false;
    reconnectA();
    return;
  }
  // Listen for Arduino #3 via Module B
  Ethernet.init(CS_B);
  if (!clientB || !clientB.connected()) {
    clientB = serverB.available();
    if (clientB) Serial.println("Arduino #3 connected to bridge!");
  }
  if (clientB && clientB.available()) {
    String msg = "";
    while (clientB.available()) {
      msg += (char)clientB.read();
    }
    msg.trim();
    Serial.print("Bridge received: "); Serial.println(msg);
    // Forward to Arduino #1 via Module A
    Ethernet.init(CS_A);
    clientA.print(msg);
    Serial.print("Bridge forwarded: "); Serial.println(msg);
  }
}
