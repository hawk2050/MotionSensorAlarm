/*
 * PIR sensor tester
 */
 #include <Arduino.h>

 void alarm(bool enable);
 void pirMotionInterrupt(void);
 
const int buzzer = 9;          // buzzer to arduino pin 9 
const int ledPin = 10;         // choose the pin for the LED
const int pirInputPin = 2;     // choose the input pin (for PIR sensor), can use for Interrupt.
const int momentaryButton = 3; // This can also be attached to an interrupt
int pirState = LOW;            // we start, assuming no motion detected
volatile int val = 0;          // variable for reading the pin status within the motionPIR interrupt
 
void setup()
{
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(pirInputPin, INPUT);     // declare PIR sensor as input
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

  pinMode(pirInputPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pirInputPin), pirMotionInterrupt, CHANGE);
 
  Serial.begin(9600);
}
 
void loop()
{
  
  if (val == HIGH)
  {            
    digitalWrite(ledPin, HIGH);  // turn LED ON
    digitalWrite(buzzer, HIGH);  // turn tone module ON
    delay(100);
    digitalWrite(ledPin, LOW);  // turn LED ON
    digitalWrite(buzzer, LOW);  // turn tone module ON
    delay(100);
    
  }
}


/* Arduino tutorial - Buzzer / Piezo Speaker
   More info and circuit: http://www.ardumotive.com/how-to-use-a-buzzer-en.html
   Dev: Michalis Vasilakis // Date: 9/6/2015 // www.ardumotive.com */

void pirMotionInterrupt()
{
  // check if the input is HIGH
  val = digitalRead(pirInputPin);  // read input value
}

