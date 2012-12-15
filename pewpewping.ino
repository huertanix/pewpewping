/*
  @file     pewpewping.pde
  @author   David Huerta
  @license  CDL (see CDL-LICENSE.txt)

  Ermahgerd! Shoot the paper website screenshot with the pressure sensor behind 
  it to DDOS! Built for Art Hack Day in San Francisco (http://arthackday.net/gaffta/)
*/

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "GAFFTA";
char pass[] = "newtemporary";
int status = WL_IDLE_STATUS; // wifi radio's status
int fsrPin = A0; // pressure sensor connected to this pin
char server[] = "www.mpaa.org";
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Captain, our shields are down!"); 
    // don't continue:
    while(true);
  }
  
  // attempt to connect to the wifis:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
   
  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
}

void loop() {
  // check the network connection once every 10 seconds:
  int fsrReading = analogRead(fsrPin);

  if (fsrReading < 1023) { // super-sensitive
    Serial.println(fsrReading);
    Serial.println("Starting connection to server...");
    
    if (client.connect(server, 80)) {
      Serial.println("connected to server");
      client.println("GET / HTTP/1.1");
      client.println("Host:www.mpaa.org");
      client.println("Connection: close");
      client.println();
    }
  }
  
  delay(50);
}
