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

volatile int val = 0;          // variable for reading the pin status within the motionPIR interrupt

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 100;           // interval at which to blink (milliseconds)
 
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
    
    // check to see if it's time to blink the LED; that is, if the difference
    // between the current time and last time you blinked the LED is bigger than
    // the interval at which you want to blink the LED.
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW)
      {
        ledState = HIGH;
      } 
      else
      {
        ledState = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(ledPin, ledState); // toggle LED
      digitalWrite(buzzer, ledState);  // toggle tone module
    }
    
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

