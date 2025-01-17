/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 * Lesson 03: Connecting a MAX7219 LED display
 */
#include "LedControl.h"

LedControl lc=LedControl(D7,D5,D2,1); //DIN: D7, CLK: D5, CS: D2, VCC: 3v, GND: G
int number = 0;
String stringNumber;
char message[8];

void writeToSegmentDisplay(char text[8]){
  lc.clearDisplay(0);
  
  for(int i=0; i<8; i++){
    lc.setChar(0,7-i,text[i],false);
  }
}
void setup() {

   // Initialize the MAX7219 device
  lc.shutdown(0,false);   // Enable display
  lc.setIntensity(0,15);  // Set brightness level (0 is min, 15 is max)
  
  writeToSegmentDisplay("Hello   ");
  
  
}

void loop() {
  // Oppgave: Skriv tall til display hvert sekund
  // TODO: nikhil fiks en bedre måte enn den stygge hacken i answers.  
}
