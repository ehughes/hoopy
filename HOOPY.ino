/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

extern "C" 
{
  #include "user_interface.h"
}
#define MY_BASE_HOSTNAME "HOOPY-"
String MyHostName;

void setup()
{
  Serial.begin(9600);

  Serial.println("starting");

   char ChipID_String[32];
    
   snprintf(ChipID_String,sizeof(ChipID_String),"%08x",(int32_t)ESP.getChipId());

   MyHostName += "HOOPY-";
   MyHostName += String(ChipID_String);
 
 
  WiFi.softAP(MyHostName.c_str());
    
  IPAddress myIP = WiFi.softAPIP();
 
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Hostname is " + MyHostName);

     
  if (!MDNS.begin("hoopy"))
    {
         Serial.println("Error setting up MDNS responder!");
   }

    //Start up the OTA loader
   ArduinoOTA.setHostname(MyHostName.c_str());

   
   MDNS.addService("http", "tcp", 80);
     
}


void loop()
{
     
        ArduinoOTA.handle();

        yield();
     

}

