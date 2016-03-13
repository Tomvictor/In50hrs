/*
  Web client

 This sketch connects to a website 
 using Wi-Fi functionality on MediaTek LinkIt platform.

 Change the macro WIFI_AP, WIFI_PASSWORD, WIFI_AUTH and SITE_URL accordingly.

 */
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
//Dht
#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)


//wifi
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

//ldr
#include <math.h>
const int ledPin=12;                 //Connect the LED Grove module to Pin8, Digital 8
const int thresholdvalue=10;         //The threshold for which the LED should turn on. 
float Rsensor; //Resistance of sensor in K

DHT dht(DHTPIN, DHTTYPE);//DHT

#define WIFI_AP "Indix-Event"
#define WIFI_PASSWORD "guest@123"
//use WPA for normal use
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SITE_URL "http://www.project.buildfromzero.com"

LWiFiClient c;

void setup()
{
  LWiFi.begin();
  Serial.begin(115200);
  //ldr
  pinMode(ledPin,OUTPUT);            //Set the LED on Digital 8 as an OUTPUT
 //DHT
  Serial.println("DHTxx Started!");
    dht.begin();

  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) //
  {
    delay(1000);
  }

  // keep retrying until connected to website
  Serial.println("Connecting to WebSite");
  while (0 == c.connect(SITE_URL, 80))
  {
    Serial.println("Re-Connecting to WebSite");
    delay(1000);
  }

  // send HTTP request, ends with 2 CR/LF
  Serial.println("send HTTP GET request");
  c.println("GET / HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Connection: close");
  c.println();

  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);
  }
}

boolean disconnectedMsg = false;

void loop()
{

//LDR
int sensorValue = analogRead(A0); 
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
 // Serial.println("the analog read data is ");
  Serial.println(sensorValue);
 // Serial.println("the sensor resistance is ");
//  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;
  //delay(1000);

//DHT
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

    //website
    float t = 0.0;
    float h = 0.0;
    
    if(dht.readHT(&t, &h))
    {
        Serial.println("------------------------------");
        Serial.print("temperature = ");
        Serial.println(t);
        
        Serial.print("humidity = ");
        Serial.println(h);
    }
    
    delay(2000);
   //DHT end
  
  // Make sure we are connected, and dump the response content to Serial
  while (c)
  {
    int v = c.read();
    if (v != -1)
    {
      Serial.print((char)v);
    }
    else
    {
      Serial.println("no more content, disconnect");
      c.stop();
      while (1)
      {
        delay(1);
      }
    }
  }

  if (!disconnectedMsg)
  {
    Serial.println("disconnected by server");
    disconnectedMsg = true;
  }


  
  delay(500);
}

