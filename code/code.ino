#include<SoftwareSerial.h>
#include <Servo.h>

#include "Barometer.h"
#include <Wire.h> SoftwareSerial BT(12,13); float temperature;
float pressure;
float atm;
float altitude;

//Barometer myBarometer;
int state = 5;
int command;
const int motor1Pin1 = 5; const int motor1Pin2 = 6; const int motor2Pin1 = 3; const int motor2Pin2 = 11; int trigPin=7;
int echoPin=8;
int motorSpeed = 1023;
long duration;
long distance; 
Servo myservo;
void setup()
{
BT.begin(38400);
//set pin modes pinMode(motor1Pin1, OUTPUT); pinMode(motor1Pin2, OUTPUT); pinMode(motor2Pin1, OUTPUT); pinMode(motor2Pin2, OUTPUT); pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT); pinMode(A0,OUTPUT); pinMode(A1,OUTPUT); Serial.begin(9600);
// myBarometer.init();
myservo.attach(9);
}

void loop()
{
myservo.write(90);
delay(15);

digitalWrite(trigPin, LOW); delayMicroseconds(2); digitalWrite(trigPin, HIGH); delayMicroseconds(10); digitalWrite(trigPin, LOW);

analogWrite(A1,1023);
analogWrite(A0,1023);

duration = pulseIn(echoPin, HIGH); distance= duration/58.2; if(distance<10)
{
Serial.println(distance);
state5();

state2();
state5();
long leftdist=lookleft();
long rightdist=lookright();
if (leftdist >10&&leftdist<1)
{
state4();
}
else if(rightdist >10)
{
state3();
}
else
{
state2();
} 
state5();
}
while(BT.available())
{
command=BT.read();
//move forward if(command =='a') {
state1();
}

//move backward if(command =='b') {
state2();
}

//turn right if(command =='c') {
state3();
}

//turn left if(command =='d') {
state4();
}

//do nothing if(command =='e')
{
state5();
}
}
}
//STATE 1: move forward void state1() {
analogWrite(motor1Pin1, motorSpeed); digitalWrite(motor1Pin2, LOW); analogWrite(motor2Pin1, motorSpeed); digitalWrite(motor2Pin2, LOW); Serial.println("F");
delay(500);
}
//STATE 2: move backward void state2() { digitalWrite(motor1Pin1, LOW);
analogWrite(motor1Pin2, motorSpeed); digitalWrite(motor2Pin1, LOW); analogWrite(motor2Pin2, motorSpeed); Serial.println("B");
delay(500);
}
//STATE 3: move right void state3() {
analogWrite(motor1Pin1, motorSpeed); digitalWrite(motor1Pin2, LOW); digitalWrite(motor2Pin1, LOW); 
analogWrite(motor2Pin2, LOW); Serial.println("R");
delay(700);
}
//STATE 4: move left void state4() { digitalWrite(motor1Pin1, LOW); analogWrite(motor1Pin2, LOW);
analogWrite(motor2Pin1, motorSpeed); digitalWrite(motor2Pin2, LOW); Serial.println("L");
delay(700);
}
//STATE 5: do nothing void state5() { digitalWrite(motor1Pin1, LOW); digitalWrite(motor1Pin2, LOW); digitalWrite(motor2Pin1, LOW); digitalWrite(motor2Pin2, LOW); Serial.println("DN");
delay(1000);
}
long lookleft() {
myservo.write(170);
delay(700);          //wait for the servo to get there digitalWrite(trigPin, LOW); delayMicroseconds(2);
digitalWrite(trigPin, HIGH); delayMicroseconds(10); digitalWrite(trigPin, LOW);

analogWrite(A1,1023);
analogWrite(A0,1023);

long duration = pulseIn(echoPin, HIGH);
long leftdist= duration/58.2;

myservo.write(90);
delay(700);                                //wait for the servo to get there
Serial.println(leftdist);
return leftdist;
}
long lookright () {
myservo.write(10);
delay(700);              //wait for the servo to get there digitalWrite(trigPin, LOW); delayMicroseconds(2);
digitalWrite(trigPin, HIGH); delayMicroseconds(10); digitalWrite(trigPin, LOW); analogWrite(A1,1023); analogWrite(A0,1023);
duration = pulseIn(echoPin, HIGH); long rightdist= duration/58.2; myservo.write(90); 
delay(700);   //wait for the servo to get there
Serial.println(rightdist);
return rightdist;
}

