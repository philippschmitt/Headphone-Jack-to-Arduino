/*
  
  HEADPHONE JACK TO ARDUINO
  Trigger a camera flash from a smart phone using a short audio impulse.
  
  Components:
  * ATTiny 85 (or any Arduino) to run the code below
  * Audio source which sends 50ms long sound impulses to an analog input pin (pin 3 on ATtiny85)
  * Transistor on digital output pin (pin 0 on ATtiny85)
  * Relay, operated from pin 0 via the transistor. Used to trigger the flash circuit and isolate it 
    from the main circuit
  * Camera flash, attached via synchron cable to the relay. Probably carries high voltages (~180V)
    and needs to be isolated from the main circuit!
  * LED connected to pin 4. Lights up, as long as the ATtiny waits for the flash to reload
    
  
  Created June 23, 2014
  by Philipp Schmitt
  
  Last modified June 23, 2014
  by Philipp Schmitt
  
*/


// DEFINE PINS

// Activates the transistor, which triggers the relay, which triggers the flash
const int triggerPin = 0;

// LED attached here
const int ledPin = 4;

// Audio source (e.g. iPhone) connected here
const int audioPin = 3;


// DEFINE OTHER VARIABLES

// Time given to the flash to reload (in ms)
const int pauseDuration = 3000;

// true while ATtiny is "recording" audio input
boolean rec = false;
// true while flash detection disabled
boolean pauseFlash = false;

// current analog value from Audio Input
int audioInput;
// analog value from audion input from last loop() cycle
int lastAudioInput = 0;
// difference between audioInput and lastAudioInput
unsigned int diff = 0;

// counter for measuring audio input duration
unsigned int counter = 0;
// duration while flash circuit is closed, i.e. flash is triggered
const int flashDuration = 100;
// Duration of audio impulse (90ms for 50ms input)
const int audioDuration = 90;

// voltage difference on audio input pin needed to trigger flash
const int triggerValue = 20;

// store the number of flashes that are yet to be triggered (interval, see pauseDuration)
unsigned int flashQueue = 0;

// store millis() for pause timing (see pauseDuration)
unsigned long startPause;
unsigned long flashPause;


void setup() {
  // Define LED pin as output pin
  pinMode(triggerPin, OUTPUT);
}


void loop() {

  // read audio input
  audioInput = analogRead( audioPin );
    
  // Turn on LED, if there are flashes waiting in the queue
  if( flashQueue > 0 ) {
    // LED on
    analogWrite( ledPin, 255); 
  } else {
    // LED off
    analogWrite( ledPin, 0); 
  }
   
  // wait for <audioDuration> ms until next audio impulse can be detected from input
  if( pauseFlash == true && abs(millis()-startPause) > audioDuration ) {
    // enable audio detection
    pauseFlash = false;
  }  
  
  // if audio detection enabled
  if( !pauseFlash ) {
   
    // calculate difference between current audio input value and value from last loop cycle
    diff = (unsigned int) abs( lastAudioInput-audioInput );
    
    // difference is larger than triggerValue needed and circuit is currently not recording
    if( diff > triggerValue && rec == false) {
      // start recording
      rec = true;
    // difference is larger than triggerValue needed and circuit is currently recording
    } else if( diff > triggerValue && rec == true) {
      // increase counter
      // (measures, if triggerValue is higher than needed over time)
      counter++;
    }
    
    // all criteria for flash met
    if( counter > 30 ) {
      
      // reset counter, stop recording
      counter = 0; 
      rec = false;
      
      // Add one flash to flash queue
      flashQueue++;
      
      // pause flash recording and store pause start time
      pauseFlash = true;
      startPause = millis();
    }
    
  }
  

  // If more than zero flashes are waiting in the queue, flash in interval defined in pauseDuration
  if( flashQueue > 0 && abs(millis()-flashPause)>pauseDuration ) {
    
    // turn on transistor, trigger flash
    digitalWrite( triggerPin, HIGH); 
    
    // remove one flash from queue
    flashQueue--;
    
    // store current time for new pause cycle
    flashPause = millis();
  }

  
  // Disable flash trigger after <duration> loop cycles
  if( abs(millis()-flashPause)>flashDuration ) {
    // turn off transistor
    digitalWrite( triggerPin, LOW);
  }
   
  // store audio input for next loop cycle
  lastAudioInput = audioInput;
  
}
