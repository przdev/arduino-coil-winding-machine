#include <rgb_lcd.h>
#include <Stepper.h>
#include <Wire.h>

const int OK = 2;
const int buzzer = 3;
const int button_INCRE = 4;
const int button_DECRE = 5;

//Change this according to one revolution steps
#define SIZE 32
rgb_lcd lcd;

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int temp;

void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.setRGB(0,0,255);
  Serial.begin(9600);
}
void setup1(){
  temp=0;
  lcd.print("WELCOME");
  lcd.setCursor(0,1);
  lcd.print("PRESS OK");
  while(digitalRead(OK)==1){}
  myTone(buzzer,1000, 400);
  lcd.clear();
  lcd.setRGB(255,10,10);
  lcd.print("Enter STEPS");
  lcd.setCursor(0,1);
  lcd.print(temp);
  while(digitalRead(OK)==1){
    if(digitalRead(button_INCRE)==0){
      temp++;
      lcd.setCursor(0,1);
      lcd.print(temp);
      delay(150);
    }
    if(digitalRead(button_DECRE)==0){
      temp--;
      lcd.setCursor(0,1);
      lcd.print(temp);
      delay(150);
    }
  }
  myTone(buzzer,1000, 400);
  lcd.clear();
  lcd.setRGB(255,255,0);
  lcd.print("SPEED");
  int sensorReading=1;
  while(digitalRead(OK)==1){
   if(digitalRead(button_INCRE)==0){
      sensorReading++;
      delay(150);
    }
    if((digitalRead(button_DECRE)==0)){
      sensorReading--;
      delay(150);
    }
   lcd.clear();
   lcd.print("SPEED(1-60)");
   lcd.setCursor(0,1);
   lcd.print(sensorReading);
   delay(100);
  }
  myTone(buzzer,1000, 200);
  lcd.clear();
  lcd.setRGB(255,10,150);
  lcd.print("PRESS OK");
  lcd.setCursor(0,1);
  lcd.print("FOR CONT..");
  myStepper.setSpeed(sensorReading);
  delay(400);
  while(digitalRead(OK)==1){}
  myTone(buzzer,1000, 300);
}
void turn(){
  int i=0;
  while(i<=SIZE*temp){
    myStepper.step(1);
    lcd.setCursor(0,1);
    lcd.print(int(i/SIZE));
    i++;
  }
  lcd.clear();
  lcd.print("DONE!");
  lcd.setCursor(0,1);
  lcd.print("PRESS BUTTON");
  while(digitalRead(OK)==1){}
  myTone(buzzer,1000, 200);
  lcd.clear();
  lcd.print("CONFORM");
  lcd.setCursor(0,1);
  lcd.print("PRESS OK");
  while(digitalRead(OK)==1){}
  myTone(buzzer,1000, 200);
}
void myTone(byte pin, uint16_t frequency, uint16_t duration){
  unsigned long startTime=millis();
  unsigned long halfPeriod= 1000000L/frequency/2;
  pinMode(pin,OUTPUT);
  while (millis()-startTime< duration)
  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(halfPeriod/8);
    digitalWrite(pin,LOW);
    delayMicroseconds(halfPeriod/8);
  }
  pinMode(pin,INPUT);
}
void loop() {
  setup1();
  lcd.clear();
  lcd.setRGB(255,10,10);
  lcd.print("STEPS");
  lcd.setCursor(0,1);
  turn();
 }