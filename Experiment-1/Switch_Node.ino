#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0x02};
IPAddress ip(192,168,1,11);
IPAddress serverIP(192,168,1,10);
const int buttonPin = 6;
bool ledState = false;
int lastButtonState = HIGH;
void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  delay(2000);
  Serial.println("CLIENT READY");
}
void loop()
{
  int currentButtonState = digitalRead(buttonPin);
  if(lastButtonState == HIGH &&
     currentButtonState == LOW)
  {
    ledState = !ledState;
    EthernetClient client;
    if(client.connect(serverIP, 80))
    {
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
    else
    {
      Serial.println("CONNECTION FAILED");
    }
    delay(300);
  }
  lastButtonState = currentButtonState;
}
