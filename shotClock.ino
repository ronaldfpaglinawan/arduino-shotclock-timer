/*
The Shot Clock Circuit code
Created by Ronald F. Paglinawan on 15/10/2017.
Copyright © 2017 Paglinawan Technologies. All rights reserved.

This code allows you to run countdown timer in 24s and 14s configuration. This ckt has 3 inputs (shortTime button, longTime button,
startPause switch) and 9 outputs (8 pins for two BCD decoders and 1 buzzer pin).
*/

// set pin numbers:
const int A0Pin =  2;				  // A0Pin - D0Pin --> BCD decoder pins for Ones 7-segment display
const int B0Pin =  3;
const int C0Pin =  4;
const int D0Pin =  5;
const int A1Pin =  6;				  // A1Pin - D1Pin --> BCD decoder pins for Tens 7-segment display
const int B1Pin =  7;
const int C1Pin =  8;
const int D1Pin =  9;
const int startButtonPin = 10;         // startPause timer pin
const int longTimeButtonPin = 11;      // 24s pushbutton pin
const int shortTimeButtonPin = 12;     // 14s pushbutton pin
const int buzzerPin = 13;

// variables will change:
int timerValue = 0;
int shortButtonState;             // the current reading from the short pin
int lastShortButtonState = LOW;   // the previous reading from the short pin
int longButtonState;             // the current reading from the long pin
int lastLongButtonState = LOW;   // the previous reading from the long pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 30;    // the debounce time; increase if the output flickers


void setup() {
  Serial.begin(9600);

  // initialize the data pins as an output:
  pinMode(A0Pin, OUTPUT);
  pinMode(B0Pin, OUTPUT);
  pinMode(C0Pin, OUTPUT);
  pinMode(D0Pin, OUTPUT);
  pinMode(A1Pin, OUTPUT);
  pinMode(B1Pin, OUTPUT);
  pinMode(C1Pin, OUTPUT);
  pinMode(D1Pin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // initialize the pushbutton pins as an input:
  pinMode(shortTimeButtonPin, INPUT);
  pinMode(longTimeButtonPin, INPUT);
  pinMode(startButtonPin, INPUT);


  // set initial value of output pins to LOW:
  decodeNumbers(0);
}

void loop() {
  // read the state of the buttons and save it into a local variable:
  int readingShortPin = digitalRead(shortTimeButtonPin);
  int readingLongPin = digitalRead(longTimeButtonPin);

  // If the switch changed, due to noise or pressing:
  if (readingShortPin != lastShortButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();

  } else if (readingLongPin != lastLongButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();

  }


  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (readingShortPin != shortButtonState) {
      shortButtonState = readingShortPin;

      if (shortButtonState == HIGH) {
        // set timerValue to 14s
        timerValue = 14;
        decodeNumbers(timerValue);
        Serial.println("timerValue is set 14s");

      }
    }

    if (readingLongPin != longButtonState) {
      longButtonState = readingLongPin;

      if (longButtonState == HIGH) {
        // set timerValue to 24s
        timerValue = 24;
        decodeNumbers(timerValue);
        Serial.println("timerValue is set 24s");

      }
    }

  }

  // save the reading.  Next time through the loop,
  lastShortButtonState = readingShortPin;
  lastLongButtonState = readingLongPin;

  if (digitalRead(startButtonPin) == HIGH) {
    // start-pause the countdown timer
    Serial.println("Start/Pause Shotclock timer");
    startCountDown(timerValue);

  }

}

void startCountDown(int time) {
  while (digitalRead(startButtonPin) == HIGH && time >= 0) {
    time--;
    timerValue = time;

    Serial.println(time);
    decodeNumbers(time);
    delay(1000); // 1 second

    if (time == 0) {
      digitalWrite(buzzerPin, HIGH);
      delay(3000);
      digitalWrite(buzzerPin, LOW);
      break;
  	}
  }

}

void decodeNumbers(int number) {

  switch(number) {
    case 1:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 2:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 3:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 4:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 5:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 6:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 7:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 8:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, HIGH);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 9:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, HIGH);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 10:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 11:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 12:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 13:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 14:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 15:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 16:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 17:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 18:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, HIGH);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 19:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, HIGH);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 20:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, HIGH);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 21:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, HIGH);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 22:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, HIGH);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 23:
    	digitalWrite(A0Pin, HIGH);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, HIGH);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    case 24:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, HIGH);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, HIGH);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;

    default:
    	digitalWrite(A0Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(C0Pin, LOW);
        digitalWrite(D0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(C1Pin, LOW);
        digitalWrite(D1Pin, LOW);
    	break;
  }
}
