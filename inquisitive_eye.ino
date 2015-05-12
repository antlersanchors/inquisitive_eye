//inquisitive_eye.ino
//i love lamp
#include <Servo.h>

#define servoTopPin 10
#define servoBottomPin 11

#define servoTopHigh 180 //define the range of the top servo's movement
#define servoTopLow 0 

#define servoBottomHigh 96 //define the values to push the bottom servo around
#define servoBottomLow 86

#define potTop A0 //just for manual control
#define potBottom A1

#define led 13 //because you never know when you might want to debug

void setup() {
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {

	switch (state){
		case 1: //inquisitiveness triggered!
			fixate();
			break;

		default: //normal behaviour as usual
			move();
			break;
	}
   
}

void move(){
	// for a random duration
	// move along a path
	// oscillate?

}

void fixate(){
	// generate some random "coordinates"
	// create a triangle of points off of this region of interest
	// alternate position between these
	// resume default behaviour after timer expires


}
