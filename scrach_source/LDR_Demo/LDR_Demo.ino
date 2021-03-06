/*
/* Grove - Light Sensor demo v1.0
* 
* signal wire to A0.
* By: http://www.seeedstudio.com
*/
#include <math.h>
const int ledPin=12;                 //Connect the LED Grove module to Pin8, Digital 8
const int thresholdvalue=10;         //The threshold for which the LED should turn on. 
float Rsensor; //Resistance of sensor in K
void setup() {
  Serial.begin(9600);                //Start the Serial connection
  pinMode(ledPin,OUTPUT);            //Set the LED on Digital 8 as an OUTPUT
}
void loop() {
  int sensorValue = analogRead(A0); 
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
 // Serial.println("the analog read data is ");
  Serial.println(sensorValue);
 // Serial.println("the sensor resistance is ");
//  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;
  //delay(1000);
}
