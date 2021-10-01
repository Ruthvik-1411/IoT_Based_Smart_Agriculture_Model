#include<Servo.h>                   //Servo libraries
const int ldr1=A0;                  //Declaring Ldr pins and error value(can be changed as per convenience)
const int ldr2=A1;
const int val=20;
int val1=0,val2=0;                  //Declaring variables to store Ldr values and their difference
int diff=0;

int mospin=A2;        //Declaring soil moisture sensor pin and variable to store the value
int mosval=0;

const int servopin=6;   //Declaring servo pin and intial position of servo
int pos=90;
int pump_pin=8;         //Declaring water pump pin connected via relay module

Servo myservo;          //Declaring an instance of servo as myservo
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);     //Initialsing serial communication
  delay(500);
  pinMode(ldr1,INPUT);    //Declaring pin modes of all the pins
  pinMode(ldr2,INPUT);
  pinMode(mospin,INPUT);
  pinMode(servopin,OUTPUT);
  pinMode(pump_pin,OUTPUT);
  myservo.attach(servopin);     //To tell servo library to that servo is attched at servo pin
  myservo.write(pos);           //Make the initial angle as 90 deg
}

void loop() {
  // put your main code here, to run repeatedly:
  diff=readval();         //Read the values from Ldrs and get the difference

  if(diff>val){           //If the difference is greater than set error value i.e bottom ldr has higher value i.e more exposed that means sun is close to bottom so decrease the angle
    if(pos>30){           //If the present angle is greater than 30 deg the keep reducing the servo angle until you get out of the condition
      pos--;
      myservo.write(pos);
      delay(10);
    }
  }
  else if(diff<-val){  //If the difference is negative and below the set the value i.e top ldr is more exposed to sun so move in that direction 
    if(pos<180){        //If the present angle is less than 180deg the keep increasing the servo angle until both are equally exposed 
      pos++;
      myservo.write(pos);
      delay(10);
    }
  }
  mosval=map(analogRead(mospin),0,1023,0,100);  //Read the moisture content from soil and map it based on data obtained from dry soil and wet soil calibrated values
  //Serial.println(mosval);               //To be used while calibrating
  if(mosval>50){                    //If the soil moisture sensor value is high i.e soil is dry then on the water pump for 2 seconds and check again
    digitalWrite(pump_pin,LOW);
    delay(2000);
    digitalWrite(pump_pin,HIGH);
  }
  else{                           //If the soil moisture sensor value is low i.e soil has good water content and is wet so keep the pump off
    digitalWrite(pump_pin,HIGH);
  }
  delay(2000);
}

int readval(){              //Function to read Ldr values
  val1=analogRead(ldr1);
  val2=analogRead(ldr2);
  diff=val1-val2;
  //Serial.print(val1);       //To be used while calibrating
  //Serial.print(",");
  //Serial.print(val2);
  //Serial.print(",");
  //Serial.print(diff);
  //Serial.print(",");
  //Serial.println(pos);
  return diff;
}
