#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
#include "DHTesp.h"

#define DHTpin 2

const char* wifiname = "ChotaBheem";  
const char* password = "BheemkiShakti";  

DHTesp dht;
WiFiClient client;  

long myChannelNumber = 1490676;
const char* myWriteAPIKey = "7OG22WM1EMYNMVTY";

int fromLow = 0;
int fromHigh = 1023;
int toLow = 0;
int toHigh = 100;

const int analogpin = A0;  // Analog input pin that the soil moisture sensor is attached to
int sensorValueFromA;         // store sensor input value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  // pinMode(analogpin, INPUT);  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(wifiname, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("NodeMCU is connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP()); 
  
  pinMode(analogpin, INPUT); 
  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to pin 2 
   
  ThingSpeak.begin(client);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValueFromA = analogRead(analogpin); //Soil moisture value.
    
  float humidity = dht.getHumidity();   //humidity
  float temperature = dht.getTemperature(); //temperature
  
  int moistureValue = map(sensorValueA , fromLow, fromHigh, toLow, toHigh);  
  //Uploading to thingspeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, abs(moistureValue-100));
  ThingSpeak.writeFields(myChannelNumber ,myWriteAPIKey);        
  delay(300); 

}
