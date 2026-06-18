#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0x01};
IPAddress ip(192,168,1,10);
EthernetServer server(80);
const int ledPin = 5;
void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("SERVER READY");
}
void loop()
{
  EthernetClient client = server.available();
  if(client)
  {
    String msg = "";
    while(client.connected())
    {
      while(client.available())
      {
        char c = client.read();
        if(c == '\n')
        {
          msg.trim();
          Serial.print("Received: ");
          Serial.println(msg);
          if(msg == "ON")
          {
            digitalWrite(ledPin, HIGH);
          }
          if(msg == "OFF")
          {
            digitalWrite(ledPin, LOW);
          }
          client.stop();
          return;
        }
        msg += c;
      }
    }
    client.stop();
  }
}
