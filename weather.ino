
// #include <SFE_BMP180.h>

#include <Wire.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <ThingSpeak.h>
// #include <ESP8266WiFi.h>

DHT dht(D3, DHT11);
// SFE_BMP180 bmp;
double T;
char status;
WiFiClient client;

long myChannelNumber = 1881185;

const char apiKey[] = "UI1HHZGFFUEHWDOV";
const char *ssid =  "Madhuri";
const char *pass =  "pass@123";
const char* server = "api.thingspeak.com";


void setup() {
  Serial.begin(115200);
  delay(10);
  // bmp.begin();
  Wire.begin();
  dht.begin();
  WiFi.begin(ssid, pass);
ThingSpeak.begin(client);

  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
    Serial.print(WiFi.status());
    Serial.println("Connecting");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  //BMP180 sensor
  // status =  bmp.startTemperature();
  // if (status != 0) {
  //   delay(status);
  //   status = bmp.getTemperature(T);

  //   status = bmp.startPressure(3);// 0 to 3
  //   if (status != 0) {
  //     delay(status);
  //     status = bmp.getPressure(P, T);
  //     if (status != 0) {

  //     }
  //   }
  // }

  //DHT11 sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //Rain sensor
  int r = analogRead(A0);
  r = map(r, 0, 1024, 0, 100);

  // Serial.println(h);
  // Serial.println(t);
  // Serial.println(r);
  // if (client.connect(server, 80)) {
  //   Serial.println(server);
    // String postStr = apiKey;
    // postStr += "&field1=";
    // postStr += String(t);
    // postStr += "&field2=";
    // postStr += String(h);
    // postStr += "&field3=";
    // // postStr += String(P, 2);
    // // postStr += "&field4=";
    // postStr += String(r);
    // postStr += "\r\n\r\n\r\n\r\n";

    // client.print("POST /update HTTP/1.1\n");
    // client.print("Host: api.thingspeak.com\n");
    // client.print("Connection: close\n");
    // client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    // client.print("Content-Type: application/x-www-form-urlencoded\n");
    // client.print("Content-Length: ");
    // client.print(postStr.length());
    // client.print("\n\n\n\n");
    // client.print(postStr);
    // thingSpeakWrite(myChannelNumber, 1, t, apiKey);
     ThingSpeak.setField(1, t );
      ThingSpeak.setField(2, h );
      ThingSpeak.setField(3, r);
      ThingSpeak.writeFields( myChannelNumber, apiKey );
      
    //  ThingSpeak.writeField(myChannelNumber, 2, h, apiKey);
    //   ThingSpeak.writeField(myChannelNumber, 3, r, apiKey);

    Serial.print("Temperature: ");
    Serial.println(t);
    Serial.print("Humidity: ");
    Serial.println(h);
    // Serial.print("absolute pressure: ");
    // Serial.print(P, 2);
    // Serial.println("mb");
    Serial.print("Rainfall: ");
    Serial.println(r);

  // }
  // client.stop();
  delay(10000);
}
