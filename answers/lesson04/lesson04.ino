/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 */
#include <ESP8266WiFi.h> 
#include <WiFiManager.h>  

void setup() {
  Serial.begin(115200);
  Serial.println("Running setup");
  
  WiFiManager wifiManager;
  wifiManager.autoConnect("WeatherStation", "12345678");

  Serial.println("Connected to WiFi");
}

void loop() {
  Serial.println("connected");
  delay(2000);
}
