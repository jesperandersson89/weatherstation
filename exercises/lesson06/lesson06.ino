/* Weather station
 * @author: Nikhil André Luthra - Bouvet Norge
 * @web: weather.labben.org
 * @web: bouvet.no / nikhil.luthra.no
 * Lesson 06 - Connect it all together!
 */
#include <ESP8266WiFi.h> 
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>  
#include <ArduinoJson.h>
#include "LedControl.h"
#include <Servo.h> 



//Oppgave: bruk ALT du har lært frem til nå for å koble sammen skjerm, servo og henting av data!!

Servo myServo;
int servoPosition;

LedControl lc=LedControl(D7,D5,D2,1); //DIN: D7, CLK: D5, CS: D2
char message[8];

WiFiClient client;
char* host = "weather.labben.org";
const int httpPort = 80;

void setup() {
  Serial.begin(115200);
  Serial.println("Running setup");
  
  WiFiManager wifiManager;
  wifiManager.autoConnect("WeatherStation");

  Serial.println("Connected to WiFi");

  lc.shutdown(0,false);   // Enable display
  lc.setIntensity(0,15);  // Set brightness level (0 is min, 15 is max)
  
  writeToSegmentDisplay("Hello   ");

  delay(2000);

  myServo.attach(D3);
  delay(200);
  servoPosition = 90;
  myServo.write(servoPosition); 

  //ProTip: detach servoen når du ikke bruker den. Det gjør den mindre utsatt for signalstøy og jitters.
  myServo.detach();
}


void writeToSegmentDisplay(char text[8]){
  lc.clearDisplay(0);
  
  for(int i=0; i<8; i++){
    lc.setChar(0,7-i,text[i],false);
  }
}

void moveServo(String symbolName){
  
  
  int newPosition = 0;
  //Info: symbolnavna kommer fra Yr: https://om.yr.no/symbol/
  //Oppgave: sett newPosition til rett posisjon i forhold til hvor du vil ha pekeren på skyen.
  //Du kan også bytte ut hvilke symbolNavn du støtter, legge til flere/færre etc.
  
  if(symbolName == "Lettskyet" || symbolName == "Sol" || symbolName == "Klarvær"){
    
  }else if(symbolName == "Skyet"){
    
  }else if(symbolName == "Lette regnbyger" || symbolName == "Regnbyger" || symbolName == "Kraftige regnbyger" || symbolName == "Lette regnbyger og torden"){
    
  }

  
  //Oppgave: vi vil kun kjøre koden under hvis det er endring i symbol/posisjon.
  //         Ingen vits å attache servoen om den ikke skal flyttes.


    
    myServo.attach(D3);
    
    delay(200);
  
    if(servoPosition < newPosition){
      for(servoPosition; servoPosition < newPosition; servoPosition += 1) 
      {                                  
        myServo.write(servoPosition);              
        delay(15);                       
      }
    }else if(servoPosition > newPosition){
      //Oppgave: for-løkke for å flytte servoen om nye posisjonen er lavere enn der vi allerede er.

      
    }  

   
     myServo.detach();

   
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
            const String symbolName = root["symbolName"];
            const String rain = root["rain"];
            const String tempType = root["temptype"];
            const String temp = root["temp"];
            
            char textArr[8];
            temp.toCharArray(textArr, 8);
            int i = temp.length();
            for(i; i<8; i++){
              textArr[i] = ' ';
            }
            
            writeToSegmentDisplay(textArr);

            delay(100);
            
            moveServo(symbolName);

           }
        
      }
}

void loop() {

  delay(1000);

  //Oppgave: Fyll ut sted
  doRequest();

  delay(10000);
}
