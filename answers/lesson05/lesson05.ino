/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 */
#include <ESP8266WiFi.h> 
#include <WiFiManager.h>  
#include <ArduinoJson.h>

WiFiClient client;
char* host = "weather.labben.org";
const int httpPort = 80;

void setup() {
  Serial.begin(115200);
  Serial.println("Running setup");
  
  WiFiManager wifiManager;
  wifiManager.autoConnect("WeatherStation", "12345678");

  Serial.println("Connected to WiFi");
}


void doRequest(String location){
      if (!client.connect(host, httpPort)) {
        Serial.println("doRequest failed"); 
      }else{
          String url = "/api/yr?location=" + location;
          
          Serial.print("requesting URL: ");
          Serial.println(url);
         
          client.print(String("GET ") + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266YrClient\r\n" +
               "Content-Type: application/json\r\n" + 
               "Connection: close\r\n\r\n");

         String c;
         // Read all the lines of the reply from server and print them to Serial
         while(client.available()){
            c = client.readStringUntil('\r\n\r\n');
         }

         DynamicJsonBuffer jsonBuffer(250);
         
         JsonObject& root = jsonBuffer.parseObject(c);
          if(!root.success()) {
            Serial.println("parseObject() failed");
          }else{
            const String message = root["display"];
            Serial.println(message);
            char text[8];
            message.toCharArray(text, 8);
            }
        
      }
}

void loop() {
  doRequest("Norge/Oslo/Oslo/Oslo/");
  delay(10000);
}
