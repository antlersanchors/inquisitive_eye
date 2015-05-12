//inquisitive_eye.ino
#include <Servo.h>

#define servoTopPin 10
#define servoBottomPin 11

#define potTop A0
#define potBottom A1


int led = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
    delay(100);               // wait for a second
}
