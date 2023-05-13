#include <IRremote.h>

// Pins
const int RECV_PIN = 11;
const int MOTOR_PIN = 2;

// IR receiver object
IRrecv receiver(RECV_PIN);

// IR signal container
decode_results results;


void setup() 
{
  Serial.begin(9600);
  receiver.enableIRIn(); // Enable the IR receiver module
  receiver.blink13(true); // Turn on the LED on pin 13 when receiving a signal
  pinMode(MOTOR_PIN, OUTPUT);
}


void loop() {
  // Check if an IR signal is received
  if (receiver.decode()) 
  {
    // Print hex value
    Serial.println(receiver.decodedIRData.decodedRawData, HEX);

    // Turn on motor (+ Button)
    if (receiver.decodedIRData.decodedRawData == 0xEA15FF00) 
    {
      digitalWrite(MOTOR_PIN, HIGH);
    }
    // Turn off motor (- Button)
    else if (receiver.decodedIRData.decodedRawData == 0xF807FF00) 
    {
      digitalWrite(MOTOR_PIN, LOW);
    }

    // Resume receiving the next value
    receiver.resume();
  }
}
