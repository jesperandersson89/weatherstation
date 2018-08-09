# weatherstation

IoT kurs med introduksjon til ESP8266, servo, 7-segment display og værapi.

# Upcoming changes

* Configurable weather location through WiFiManager?
* PCB for easier connection etc

# Excercises

1.  Hello World
2.  Hello Servo
3.  Hello display
4.  Hello WiFiManager
5.  Hello Weather API
6.  Combine everything you have learned!

# Hardware

* ESP8266
* Microservo
* 7-segment 8-digit display
* laserkuttet deler

# Software (3rd party libraries)

* WiFiManager
* LedControl for MAX7219 (either use the one from Library Manager and do the AVR fix (see below), or install modified library from Nikhil André Luthras GitHub repo here: https://github.com/9khil/LedControl)

# API

* This course uses weather data from Yr.no, but with a custom endpoint that just returns the data we are looking for. Probably not usable for anything else than this. The endpoint has a 20 minute cache in place.
  Url: http://weather.labben.org/api/yr/?location=**enter location from yr.no\*\*
  Example url: http://weather.labben.org/api/yr/?location=Norge/Oslo/Oslo/Oslo/

# Extra

Weather symbols and texts: https://om.yr.no/symbol/

# Contact

Contact Nikhil André Luthra if you need to know anything :)

# AVR Fix for ESP8266

`#if (defined(__AVR__)) #include <avr\pgmspace.h> #else #include <pgmspace.h> #endif`
