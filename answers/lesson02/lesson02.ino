/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 */

 #include <Servo.h> 
 Servo myServo;
 int servoPosition;
 
void setup() {
  
  // Oppgave: Attach servo på Pin D2 til servoobjektet
  myServo.attach(D2);
}

void loop() {
  // Oppgave: Kjør servo fra posisjon 0 til 180
  for(servoPosition = 0; servoPosition <= 180; servoPosition += 1) 
  {                                  
    myServo.write(servoPosition);              
    delay(15);                       
  }

  // Oppgave kjør servo fra posisjon 180 til 0
  for(servoPosition = 180; servoPosition>=0; servoPosition-=1)     
  {                                
    myServo.write(servoPosition);              
    delay(15);                       
  } 
  
}
