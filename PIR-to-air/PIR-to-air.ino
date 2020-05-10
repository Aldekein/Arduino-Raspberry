/*  Pir sensor, transmitting on 443Mhz its value */

#include <RH_ASK.h>             // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h>                // Include dependant SPI Library

// Configurable variables
int ledPin = LED_BUILTIN;       // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int calibrationTime = 30;       // the time we give the sensor to calibrate (10-60 secs according to the datasheet)
const char *shoutMsg = "black-baltic-sheep:1"; // sensor ID and value that will be broadcasted via radio

// Rest of variables
int outputPin = 12;             // pin 12 is default for the library (for 433 Mhz radio module) -- not used, reference only
int pirState = LOW;             // we start, assuming no motion detected
int pirValue = 0;               // variable for reading the pin status
RH_ASK rfDriver;               // create Amplitude Shift Keying (ASK) Object


void calibrateSensor() {
  // give the sensor some time to calibrate
  Serial.print("Calibrating sensor");
    for(int i = 0; i < calibrationTime; i++) {
      Serial.print(".");
      delay(900);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);      
    }
    Serial.println(" done!");
}

void initRadio() {
    // Initialize ASK Object
    if (!rfDriver.init()) {
      Serial.println("Failed to init radio!");
    }
}

void transmitAlert()
{
  rfDriver.send((uint8_t *)shoutMsg, strlen(shoutMsg));
  rfDriver.waitPacketSent();
}

void pirLoopHandler() {
  pirValue = digitalRead(inputPin);
  if (pirValue == HIGH) {          
    digitalWrite(ledPin, HIGH);
    if (pirState == LOW) {
      // we have just turned on
      // We only want to print on the output change, not state
      Serial.println("Motion detected!");
      pirState = HIGH;
      transmitAlert();
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH){
      // we have just turned of
      // We only want to print on the output change, not state
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input

  Serial.begin(9600);

  calibrateSensor();
  initRadio();
}


void loop() {
  pirLoopHandler();
}
