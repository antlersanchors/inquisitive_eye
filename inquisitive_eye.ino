//inquisitive_eye.ino
//i love lamp
#include <Servo.h>

#define servoTopPin 6
#define servoBottomPin 5

#define servoTopHigh 180 //define the range of the top servo's movement
#define servoTopLow 0 

#define servoBottomRight 96 //define the values to push the bottom servo around
#define servoBottomStop 90
#define servoBottomLeft 86

#define moveLow 800 //lower and upper limits for move duration
#define moveHigh 1500

#define fixateLow 2500 //lower and upper limits for staring duration
#define fixateHigh 4000
#define fixatePhase 600

#define topTravelHigh 50 //how far should it increment in one move?
#define topTravelLow -50

#define potTop A0 //just for manual control
#define potBottom A1


// ------- LED VARIABLES ---------
unsigned int red;
unsigned int green;
unsigned int blue;
bool goingUp = true;

const int redLEDPin = 9;     // LED connected to digital pin 10
const int greenLEDPin = 10;    // LED connected to digital pin 9
const int blueLEDPin = 11;    // LED connected to digital pin 11

int var = 0;

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
  Serial.begin(9600);

// ----- LED STUFF -----
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  red = 150;
  green = 200;
  blue = 10;


// ----- SERVO STUFF -----
  servoTop.attach(servoTopPin);
  servoBottom.attach(servoBottomPin);
  

  prevTime = millis();
  randomSeed(analogRead(A5)); //initialize our random num generator with noise from the pin!
  moveDuration = int(random(moveLow,moveHigh)); //initialize move duration

  newTopPos = 0;

  currentState = 0;
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
			focusFlash();
			break;

		default: //normal behaviour as usual
			move();
			gentlePulsate();
			// ledTest();
			delay(10);
			break;
	}
}
void ledTest() {
	analogWrite(redLEDPin, red);
	analogWrite(greenLEDPin, green);
	analogWrite(blueLEDPin, blue);

}

void gentlePulsate(){

	if ((goingUp == true) && (blue < 200) && (millis() % 20 == 0)){
		blue += 1;
		green += 1;
		blue += 1;

	} else if ((goingUp == true) && (blue >= 200)) {
		goingUp = false;

	} else if ((goingUp == false) && (blue >= 2) && (millis() % 20 == 0)) {
		blue -= 1;
		green -= 1;
		blue -= 1;

	} else {
		goingUp = true;
	}
	
	analogWrite(redLEDPin, red);
	analogWrite(greenLEDPin, green);
	analogWrite(blueLEDPin, blue);
}

void focusFlash(){
	red = 180;
	blue = 50;
	green = 50;

	analogWrite(redLEDPin, red);
	analogWrite(greenLEDPin, green);
	analogWrite(blueLEDPin, blue);
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
			fixateState = 1;
			break;
		case 1: //move around that point!
			servoTop.write(newTopPos);
			if ((currentTime - prevTime) % fixatePhase == 6){
				fixateState = 2;
			}
		case 2: //move around that point!
			servoTop.write(newTopPos + 20);
			if ((currentTime - prevTime) % fixatePhase == 6){
				fixateState = 1;
			}
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