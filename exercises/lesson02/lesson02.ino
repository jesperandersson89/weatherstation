/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 * Lesson 02: Controlling a servo
 */

 #include <Servo.h> 
 Servo myServo;
 int servoPosition;
 
void setup() {
  
  // Oppgave: Attach servo på Pin D3 til servoobjektet


  delay(100);
  
  //Oppgave: sett servo posisjonen til 90.
  //OBS: når servoen har flyttet seg til posisjon 90, KUTT STRØMMEN ved å ta ut USB-kabelen.
  //Når du har tatt strømmen i posisjon 90, skal du  skru på den største hvite vingen du finner i servopakken. Denne skal peke rett opp.
  

  delay(5000);
  
}

void loop() {
  // Oppgave: Kjør servo fra posisjon 0 til 180
  // Husk delay på ca 15 ms etter hver endring av servoposisjon
  for(servoPosition = 0; servoPosition <= 180; servoPosition += 1) 
  {                                  
    
  }

  // Oppgave kjør servo fra posisjon 180 til 0.
  // Husk delay på ca 15 ms etter hver endring av servoposisjon



  //Oppgaven er bestått når servoen flytter seg fra 0 til 180 og tilbake ved å ha vingen pekende oppover mot skya hele tiden. 
  //Hvis servoens vinge peker nedover, må du snu servoen. 
  
}
