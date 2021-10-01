#include <ESP8266WiFi.h>        //Libraries to use wifi functions
#include <WiFiClient.h>
#include <ThingSpeak.h>         //To connect to thingspeak platform and read/write data to fields
const char* ssid = "xxxxxx";   //Wifi name and password
const char* password = "xxxxxxx";
WiFiClient client;              //Declaring an instance of wifi client as client
unsigned long myChannelNumber = xxxxxxx;      //Thingspeak channel number
const char * myWriteAPIKey = "xxxxxxxxxxxxxxxx";  //Thingspeak write api key to write data onto the field

int mospin=A0;      //Declaring soil moisture pin and variable to store the value
int mosval=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);     //Begin serial communication
  pinMode(mospin,INPUT);
  delay(500);
  //Serial.println();         //To be used while calibrating
  //Serial.println();
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);     //Connect to the wifi with given username and password
  while (WiFi.status() != WL_CONNECTED) //Keep checking everu 0.5 seconds until wifi is connected
  {
  delay(500);
  //Serial.print(".");
  }
  //Serial.println("");         //To be used while calibrating
  //Serial.println("WiFi connected");
  //Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);     //Begin the client as this node mcu server and connect to thingspeak 
}

void loop() {
  // put your main code here, to run repeatedly:
  mosval=map(analogRead(mospin),0,1023,0,100);    //Read the sensor value and map it according to data obtained from calibration of wet,dry soil. Should be done after calibrating the sensor with soil
  //Serial.println(mosval);   //To be used while calibrating
  delay(2000);

  ThingSpeak.writeField(myChannelNumber, 1, mosval, myWriteAPIKey); //Write to the thingspeak channel with this channel number, field number, this variable, using this write api key
  //Serial.println("Channel 1 transmitted");
  delay(30000);     //Wait for 30 seconds and read the value and transmit again
}
