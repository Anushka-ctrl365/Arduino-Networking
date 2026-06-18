#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0x10};
IPAddress ip(192,168,0,200);
EthernetServer server(80);
void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  Ethernet.init(10);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("RECEIVER READY");
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());
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
            digitalWrite(5, HIGH);
            Serial.println("LED ON");
          }
          if(msg == "OFF")
          {
            digitalWrite(5, LOW);
            Serial.println("LED OFF");
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
