/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;
String bufer;
String bufer2="\n";

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));
    
    pinMode(7, OUTPUT);

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 300000;

    Serial.println();
}


void loop() { 
    bufer="AT$SF=";
    printValues();
    delay(delayTime);
}


void printValues() {
    Serial.print("Temperature = ");
    int temp=bme.readTemperature();
    Serial.print(temp);
    Serial.println(" *C");
    add_int(temp);
    Serial.print("Pressure = ");
    float presion=bme.readPressure() / 100.0F;
    Serial.print(presion);
    Serial.println(" hPa");
    add_float(presion);
    Serial.print("Approx. Altitude = ");
    float altura=bme.readAltitude(SEALEVELPRESSURE_HPA);
    Serial.print(altura);
    Serial.println(" m");
    add_float(altura);
    Serial.print("Humidity = ");
    int hum=bme.readHumidity();
    Serial.print(hum);
    Serial.println(" %");
    add_int(hum);
    Serial.println();
    send_message(bufer);
}

void add_float(float var1)
{
  byte* a1 = (byte*) &var1;
  String str1;
  //agregamos al comando AT$SF= nuestra informacion a enviar
  for(int i=0;i<4;i++)
  {
    str1=String(a1[i], HEX);
    if(str1.length()<2)
    {
      bufer+=0+str1;
    }
    else
    {
      bufer+=str1;
    }
  }
}
void add_int(int var2)
{
  byte* a2 = (byte*) &var2;
  String str2;
  str2=String(a2[0], HEX);
  if(str2.length()<2)
  {
    bufer+=0+str2;
  }
  else
  {
    bufer+=str2;
  }
}
void send_message(String payload)
{
  bufer+=bufer2;
  //*******************
  //Habilitamos el modulo Sigfox
  digitalWrite(7, HIGH);
  delay(1000);
  //Reset del canal para asegurar que manda en la frecuencia correcta
  Serial.print("AT$RC\n"); 
  //************************
  //Enviamos la informacion por sigfox
  Serial.print(bufer);
  delay(3000);
  //deshabilitamos el modulo Sigfox
  digitalWrite(7, LOW);
  //delay(500);
}
