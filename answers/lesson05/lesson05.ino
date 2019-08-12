/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 * Lesson 05 - Connect to WiFi and read weather data
 */
#include <ESP8266WiFi.h> 
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>  
#include <ArduinoJson.h>

WiFiClient client;
char* host = "weather.labben.org";
const int httpPort = 80;

void setup() {
  Serial.begin(115200);
  Serial.println("Running setup");
  
  WiFiManager wifiManager;
  wifiManager.autoConnect("WeatherStation");

  Serial.println("Connected to WiFi");
}


void doRequest(String location){
      if (!client.connect(host, httpPort)) {
        Serial.println("doRequest failed"); 
      }else{
          String url = "/api/yr/?location=" + location;
          
          Serial.print("requesting URL: ");
          Serial.print(host);
          Serial.println(url);
         
          client.print(String("GET ") + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266YrClient\r\n" +
               "Content-Type: application/json\r\n" + 
               "Connection: close\r\n\r\n");

         // Check HTTP status
          char status[32] = {0};
          client.readBytesUntil('\r', status, sizeof(status));
          if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
            Serial.print(F("Unexpected response: "));
            Serial.println(status);
            return;
          }
        
          // Skip HTTP headers
          char endOfHeaders[] = "\r\n\r\n";
          if (!client.find(endOfHeaders)) {
            Serial.println(F("Invalid response"));
            return;
          }
  
         DynamicJsonBuffer jsonBuffer(250);
         
         JsonObject& root = jsonBuffer.parseObject(client);
          if(!root.success()) {
            Serial.println("parseObject() failed");
          }else{
            const String statusText = root["status"];
            const String text = root["symbolName"];
            const String rain = root["rain"];
            const String tempType = root["temptype"];
            const String temp = root["temp"];
            const string time = jsonDocument["time"];
            
            Serial.println(statusText);
            Serial.println(text);
            Serial.println(rain);
            Serial.println(tempType);
            Serial.println(temp);
            Serial.println(time);
            

           }
        
      }
}

void loop() {
  doRequest("Norge/Oslo/Oslo/Oslo");
  
  delay(10000);
}
