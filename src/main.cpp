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
    if (pirState == LOW)
    {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      alarm(true);
    }
  } else
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
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

void alarm(bool enable)
{
  if(enable)
  {
    // Whoop up
    for(int hz = 440; hz < 1000; hz++)
    {
      tone(buzzer, hz, 50);
      delay(5);
    }
    noTone(buzzer);
  
    // Whoop down
    for(int hz = 1000; hz > 440; hz--)
    {
      tone(buzzer, hz, 50);
      delay(5);
    }
    noTone(buzzer);
  }
} // Repeat