//Libraries
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
const int LOADCELL_DOUT1_PIN = 7;
const int LOADCELL_SCK1_PIN = 8;
const int LOADCELL_DOUT2_PIN = 9;
const int LOADCELL_SCK2_PIN = 10;
//Adjustment settings
const long LOADCELL_OFFSET = 50682624;
const long LOADCELL_DIVIDER = 5895655;

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
float distance;

dht11 DHT11;
HX711 loadcell_1,loadcell_2;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(gas_sensor,INPUT);

  loadcell_1.begin(LOADCELL_DOUT1_PIN, LOADCELL_SCK1_PIN);
  loadcell_1.set_scale(LOADCELL_DIVIDER);
  loadcell_1.set_offset(LOADCELL_OFFSET);

  loadcell_2.begin(LOADCELL_DOUT2_PIN, LOADCELL_SCK2_PIN);
  loadcell_2.set_scale(LOADCELL_DIVIDER);
  loadcell_2.set_offset(LOADCELL_OFFSET);

}

StaticJsonDocument<1000> jsonBuffer;
JsonObject value = jsonBuffer.to<JsonObject>();

void loop() {
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): \t");
  Serial.print(DHT11.humidity);

  Serial.print("\tTemperature (C): ");
  Serial.print(DHT11.temperature);
  //value["dustbin"]=dustbin_ultra();

  //MQ05 Gas sensor Code for Mega
  Serial.print("\t Gas: "); 
  Serial.print(analogRead(gas_sensor));
  Serial.print("\t Distance: ");
  Serial.print(dustbin(trigPin,echoPin));
  Serial.println();
  delay(1000);

}

float dustbin(int trigPin, int echoPin)
{
  float distance,duration;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  return distance; 
}
