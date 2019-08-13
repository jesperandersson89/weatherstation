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
  

  //Oppgave: kall autoConnect på WiFiManager objektet over, og bruk en unik SSID (feks "Nikhils weatherstation"). Passord er valgfritt.
  // Dette vil starte opp et access point, som du må koble deg til for å konfigurere hvilket nettverk ESP8266 skal koble seg til.
  

  Serial.println("Connected to WiFi!");
}

void loop() {
  Serial.println("connected");
  delay(2000);
}
