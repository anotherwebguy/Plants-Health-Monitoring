
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
#include "DHT.h"

#define DHTpin 0
#define DHTTYPE DHT11

DHT dht(DHTpin,DHTTYPE);

const char* wifiname = "redmi";  
const char* password = "22222222";  

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
  Serial.begin(9600); 
  dht.begin();
  // pinMode(analogpin, INPUT);  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(wifiname);  
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
   
  ThingSpeak.begin(client);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValueFromA = analogRead(analogpin); //Soil moisture value.
  delay(500);
  float humidity = dht.readHumidity();   //humidity
  Serial.print(dht.readHumidity());
  delay(500);
  float temperature = dht.readTemperature(); //temperature
  if(isnan(temperature)){
     temperature=0;
  }
  if(isnan(humidity)){
    humidity=0;
  }
  float percentage = (100.00 - ( (sensorValueFromA/1023.00) * 100.00 ) );
  if(percentage<0){
    percentage=0;
  }
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature); 
  Serial.println("C  ");
  Serial.print("Moisture = ");
  Serial.print(percentage); 
  Serial.println("%  ");
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, abs(percentage));
  ThingSpeak.writeFields(myChannelNumber ,myWriteAPIKey);        
  delay(1000); 

}
