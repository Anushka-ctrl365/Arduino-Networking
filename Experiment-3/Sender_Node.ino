#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0x11};
IPAddress ip(192,168,0,201);
IPAddress receiverIP(192,168,0,200);
bool ledState = false;
bool lastState = HIGH;
void setup()
{
  Serial.begin(9600);
  pinMode(6, INPUT_PULLUP);
  Ethernet.init(10);
  Ethernet.begin(mac, ip);
  Serial.println("SENDER READY");
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());
}
void loop()
{
  bool currentState = digitalRead(6);
  if(lastState == HIGH && currentState == LOW)
  {
    Serial.println("BUTTON DETECTED");
    ledState = !ledState;
    EthernetClient client;
    if(client.connect(receiverIP,80))
    {
      Serial.println("CONNECTED");
      if(ledState)
      {
        client.println("ON");
        Serial.println("ON SENT");
      }
      else
      {
        client.println("OFF");
        Serial.println("OFF SENT");
      }
      delay(100);
      client.stop();
    }
    delay(300);
  }
  lastState = currentState;}
