/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 * Lesson 04: Using WiFi manager
 */
#include <ESP8266WiFi.h> 

//Oppgave: inkluder WiFiManager biblioteket fra tzapu

void setup() {
  Serial.begin(115200);
  Serial.println("Running setup");
  
  //Oppgave: opprett WiFiManager objekt.
  

  //Oppgave: kall autoConnect på WiFiManager objektet over, og bruk en unik SSID. Passord er valgfritt.
  



  //
  Serial.println("Connected to WiFi!");
}

void loop() {
  Serial.println("connected");
  delay(2000);
}
