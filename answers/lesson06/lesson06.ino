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

  if(symbolName == "Lettskyet" || symbolName == "Sol" || symbolName == "Klarvær"){
    newPosition = 100;
  }else if(symbolName == "Skyet"){
    newPosition = 170;
  }else if(symbolName == "Lette regnbyger" || symbolName == "Regnbyger" || symbolName == "Kraftige regnbyger" || symbolName == "Lette regnbyger og torden"){
    newPosition = 70;
  }

  
  if(newPosition != servoPosition){
    
    myServo.attach(D3);
    
    delay(200);
  
    if(servoPosition < newPosition){
      for(servoPosition; servoPosition < newPosition; servoPosition += 1) 
      {                                  
        myServo.write(servoPosition);              
        delay(15);                       
      }
    }else if(servoPosition > newPosition){
      for(servoPosition; servoPosition > newPosition; servoPosition-=1)     
      {                                
        myServo.write(servoPosition);              
        delay(15);                       
      }
    }  

   
     myServo.detach();

   }
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
  
          DynamicJsonDocument jsonDocument(250);
         
          deserializeJson(jsonDocument, client);
          if(!jsonDocument.containsKey("status")) {
            Serial.println("parseObject() failed");
          }else{
            const String statusText = jsonDocument["status"];
            const String symbolName = jsonDocument["symbolName"];
            const String rain = jsonDocument["rain"];
            const String tempType = jsonDocument["temptype"];
            const String temp = jsonDocument["temp"];
            
            Serial.println(symbolName);
            Serial.println(rain);
            Serial.println(tempType);
            Serial.println(temp);
            
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

  doRequest("Norge/Oslo/Oslo/Oslo");

  delay(10000);
}
