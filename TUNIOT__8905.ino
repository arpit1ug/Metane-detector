#include <ESP8266WiFi.h>

WiFiServer server(80);
//IPAddress staticIP270_10(192,168,1,10);
//IPAddress gateway270_10(192,168,1,1);
//IPAddress subnet270_10(255,255,255,0);


void setup()
{
  Serial.begin(250000);

    WiFi.disconnect();
  delay(1000);
  
  Serial.println("");
  Serial.println("Connecting to opbwlan");
 // WiFi.config(staticIP270_10, gateway270_10, subnet270_10);
   WiFi.begin("opbwlan","quiteobvious");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print(".");

  }
  
  Serial.println("Connected");
  Serial.println((WiFi.localIP()));
  server.begin();
 
}
void loop()
{
    WiFiClient client = server.available();
    client.setNoDelay(1);
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/octet-stream");
    client.println("Content-Disposition: attachment; filename='methane.hex'");
    client.println("");
    int prev=millis();
    for(int i=0;i<100000;i++)
    {
      if(millis()-prev<2)
      {
        uint8_t a=(analogRead(A0));
        client.write(a);
        prev=millis();
      }
     }
    client.stop();
    delay(1);

}
