//Libraries
#include<SoftwareSerial.h>
#include <dht11.h>
#include <ArduinoJson.h>
#include "HX711.h"


//define DHT11 pin
#define DHT11PIN A0

// defines Ultrasonic pins numbers
const int trigPin = 6;
const int echoPin = 7;

//for MQ05 gas sensor
int gas_sensor=A3;
int gas_value;

// HX711 circuit wiring
const int LOADCELL_DOUT1_PIN = 2;
const int LOADCELL_SCK1_PIN = 3;
const int LOADCELL_DOUT2_PIN = 9;
const int LOADCELL_SCK2_PIN = 10;

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
int distance;

dht11 DHT11;
HX711 loadcell_1,loadcell_2;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(gas_sensor,INPUT);

  loadcell_1.begin(LOADCELL_DOUT1_PIN, LOADCELL_SCK1_PIN);
  loadcell_1.set_scale(460);
  loadcell_1.tare();

  loadcell_2.begin(LOADCELL_DOUT2_PIN, LOADCELL_SCK2_PIN);
  loadcell_2.set_scale(460);
  loadcell_2.tare();

}

void loop() {
  int chk = DHT11.read(DHT11PIN);
  int load1=loadcell_1.get_units(5);
  int load2=loadcell_2.get_units(5);

  StaticJsonDocument<1000> jsonBuffer;
  jsonBuffer["temp"]=DHT11.temperature;
  jsonBuffer["Humidity"]=DHT11.humidity;

  //MQ05 Gas sensor Code for Mega 
  jsonBuffer["gas"]=(analogRead(gas_sensor));

  jsonBuffer["dustbin"]=(dustbin(trigPin,echoPin));
  jsonBuffer["load1"]=load1;
  jsonBuffer["load2"]=load2;
  serializeJsonPretty(jsonBuffer,Serial);
  Serial1.println();
  delay(1000);

}

int dustbin(int trigPin, int echoPin)
{
  int distance, value;
  float duration;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  value=34-(int)duration*0.034/2;
  distance=(int)value*2.94;

  return distance; 
}
