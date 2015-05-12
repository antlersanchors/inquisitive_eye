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

#define fixateLow 1500 //lower and upper limits for staring duration
#define fixateHigh 3000
#define fixatePhase 600

#define topTravelHigh 50 //how far should it increment in one move?
#define topTravelLow -50

#define potTop A0 //just for manual control
#define potBottom A1

#define led 13 //because you never know when you might want to debug

long currentTime;
long prevTime;
int moveDuration;
int bottomState;
int currentState;

int fixateDuration;
int fixateState;

int newTopPos;

Servo servoTop;
Servo servoBottom;

void setup() {
  pinMode(led, OUTPUT);

  servoTop.attach(servoTopPin);
  servoBottom.attach(servoBottomPin);
  
  Serial.begin(9600);

  prevTime = millis();
  randomSeed(analogRead(A5)); //initialize our random num generator with noise from the pin!
  moveDuration = int(random(moveLow,moveHigh)); //initialize move duration

  newTopPos = 0;

  currentState = 1;
  fixateState = 0;

  fixateDuration = int(random(fixateLow, fixateHigh));

  bottomState = servoBottomStop; //start off still
  servoBottom.write(bottomState);
  servoTop.write(servoTopLow);

}

void loop() {

	switch (currentState){
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
		servoTop.write(newTopPos);


	} else { 
		moveDuration = int(random(moveLow,moveHigh)); //new duration of the next move sequence
		newTopPos = int(random(servoTopLow, servoTopHigh));
		prevTime = millis();

	}

	// for a random duration
	// move along a path
	// oscillate?

}

void fixate(){
	currentTime = millis();

	switch (fixateState){
		case 0: //pick a point to fixate on!
			newTopPos = int(random(servoTopLow, servoTopHigh));
			servoTop.write(newTopPos);
			fixateState = 1;
			prevTime = millis();
			break;
		case 1: //move around that point!
			servoTop.write(newTopPos + 50);
			if ((currentTime - prevTime) % fixatePhase == 1){
				fixateState = 2;
			}
			break;
		case 2:
			servoTop.write(newTopPos - 50);
			if ((currentTime - prevTime) % fixatePhase == 2){
				fixateState = 3;
			}
			break;
		case 3:
			servoTop.write(newTopPos);
			break;
	}

	if (currentTime - prevTime >= fixateDuration){ //done staring? return to the default state
		fixateState = 0;
		prevTime = millis();
		// currentState = 0;
	}	

	// generate some random "coordinates"
	// create a triangle of points off of this region of interest
	// alternate position between these
	// resume default behaviour after timer expires

}