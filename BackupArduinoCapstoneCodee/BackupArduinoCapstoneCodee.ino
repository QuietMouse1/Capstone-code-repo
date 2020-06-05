#include "SMPWM01A.h"
#include <dht.h>


SMPWM01A dust;
dht DHT;
#define DHT11_PIN 7

int analog_IN = A0;  // This is our input pin

float data[5];

void setup () { 
  
  Serial.begin(9600);
  dust.begin();
  pinMode(analog_IN, INPUT);
 
}
struct Data{
  float pm2;
  float pm10;
  double temperature;
  double humidity;
  int light_val;
};


void loop() {
 
  //Print the small particle concentration, 1-3um in size
  //Measurement (should be) in ug/m^3
  //Serial.print("PM2.5: ");
  data[0]= dust.getPM2();
  //Serial.println(data[0]);
  
  //Print the large particle concentration, ~10um in size
  //Measurement (should be) in ug/m^3
  //Serial.print("PM10: ");
  data[1] = dust.getPM10();
  //Serial.println(data[1]);

  int chk = DHT.read11(DHT11_PIN);
  data[2] = DHT.temperature;  
  //Serial.print("Temperature = ");
  //Serial.println(data[2]);
  data[3]= DHT.humidity;
  //Serial.print("Humidity = ");
  //Serial.println(data[3]);

  int light_val = analogRead(analog_IN);  
  data[4] = light_val;
  //Serial.print("Light  read: ");
  //Serial.println(data[4],DEC);

  delay (1000);
  for (int i = 0; i <5; i++){
  Serial.print(data[i]);
  Serial.print(',');
  }
  Serial.println();
  
  delay(2000);
  
}
