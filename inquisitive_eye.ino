//inquisitive_eye.ino
//i love lamp
#include <Servo.h>

#define servoTopPin 10
#define servoBottomPin 11

#define servoTopHigh 180 //define the range of the top servo's movement
#define servoTopLow 0 

#define servoBottomRight 96 //define the values to push the bottom servo around
#define servoBottomStop 90
#define servoBottomLeft 86

#define moveLow 100 //lower and upper limits for move duration
#define moveHigh 800

#define topTravelHigh 50 //how far should it increment in one move?
#define topTravelLow -50

#define potTop A0 //just for manual control
#define potBottom A1

#define led 13 //because you never know when you might want to debug

long currentTime;
long prevTime;
int moveDuration;
int bottomState;

Servo servoTop;
Servo servoBottom;

void setup() {
  pinMode(led, OUTPUT);

  servoTop.attach(servoTopPin);
  servoBottom.attach(servoBottomPin);
  
  Serial.begin(9600);

  prevTime = millis();
  randomSeed(analogRead(A5); //initialize our random num generator with noise from the pin!
  moveDuration = int(random(moveLow,moveHigh)); //initialize move duration

  bottomState = 

}

void loop() {

	switch (value){
		case 1: //inquisitiveness triggered!
			fixate();
			break;

		default: //normal behaviour as usual
			move();
			break;
	}
   
}

void move(){
	currentTime = millis();

	if (currentTime - prevTime <= moveDuration) { //have we finished the move yet?


	} else { 
		moveDuration = int(random(moveLow,moveHigh)); //new duration of the next move sequence
		prevTime = millis();

	}

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
