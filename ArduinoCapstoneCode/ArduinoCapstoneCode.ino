/*
PM1.PM2.5,PM10,VisibleLight,IR,UV,CO2,TEMP,HUMIDITY
*/

#include <Seeed_HM330X.h> //PMOD 2.5 Air quality lib
#include <Wire.h>
#include "Arduino.h"
#include "SI114X.h" //Sunlight sensor
#include "SCD30.h" // CO2 and sunlight sensor


HM330X pm_Sensor;
uint8_t buf[30];
SI114X SI1145 = SI114X();


const char* str[] = {"pm_Sensor num: ", "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                     "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
                     "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
                    };

/*30s*/
void setup() {
  Wire.begin();
  Serial.begin(9600);
  scd30.initialize();
  Serial.println("SCD30 Raw Data");

  delay(100);
  Serial.println("Beginning HM330X");
  if (pm_Sensor.init()) {
    Serial.println("HM330X init failed!!!");
    while (1);
  }

  Serial.println("Beginning Si1145!");
  while (!SI1145.Begin()) {
    Serial.println("Si1145 is not ready!");
    delay(1000);
  }
  Serial.println("Si1145 is ready!");


}


void loop() {
  if (pm_Sensor.read_sensor_value(buf, 29)) {
    Serial.println("HM330X read result failed!!!");
  }
 //parse_result_value(buf);
  parse_result(buf);
  Serial.print(SI1145.ReadVisible());
  Serial.print(",");
  Serial.print(SI1145.ReadIR());
  Serial.print(",");
  //the real UV value must be div 100 from the reg value , datasheet for more information.
  Serial.print((float)SI1145.ReadUV() / 100);
  Serial.print(",");
  
  float result[3] = {0};
  if (scd30.isAvailable()) {
    scd30.getCarbonDioxideConcentration(result);
    //Serial.print("Carbon Dioxide Concentration is: ");
    Serial.print(result[0]);
    Serial.print(" ppm");
    Serial.print(",");
    //Serial.print("Temperature = ");
    Serial.print(result[1]);
    Serial.print(" ℃");
    Serial.print(",");
    //Serial.print("Humidity = ");
    Serial.print(result[2]);
    Serial.print("%");
    Serial.println();
  }
  delay(30000);
  Serial.flush();
  
}
