#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define WIFI_SSID "Ahsan"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "kabir123"  

#define FIREBASE_HOST "smart-kitchen-aac83.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "362XqYWvt2lMoVsxYfWNMmONqcX1nxmpywqeZxcX"            // the secret key generated from firebase


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

    // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


}
String path = "9FbP47wyKDUREHziot5J4OcxyD72";

void loop() {
  if(Serial.available()>0)
  {
    StaticJsonBuffer<1000> jsonBuffer;
    JsonObject& doc = jsonBuffer.parseObject(Serial);

    int dust=doc["dustbin"];
    double gas=doc["gas"];
    int temp=doc["temp"];
    double hum=doc["Humidity"];
    double load1=doc["load1"];
    double load2=doc["load2"];
    Serial.println(dust);
    Serial.println(temp);
    Serial.println(gas);
    Serial.println(hum);
    Serial.println(load1);
    Serial.println(load2);

    Firebase.set(path+"/sensor", doc);
    delay(500);
    
    
//  if(Firebase.updateNode(firebaseData, path, dustbin))
//    {
//      Serial.println(firebaseData.jsonString());
//    }
//  else
//    {
//      Serial.println(firebaseData.errorReason());
//    }
  }
  
}
