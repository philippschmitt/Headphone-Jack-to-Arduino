
boolean rec = false,
        pauseFlash = false;

int sensorValue, 
    lastValue = 0, 
    diff = 0, 
    counter = 0,
    flashQueue = 0,
    nextDevice = 0,
    
    startPause,
    flashPause,
    pause = 3000,
    duration = 100;
    

void setup() {
  // LED Pin
  pinMode(0, OUTPUT);
}


void loop() {
  
  // LED an, wenn Blitze im Queue
  if( flashQueue > 0 ) {
       analogWrite(4, 300); 
  } else {
     analogWrite(4, 0); 
  }
 
  // Zählen, bis neuer Blitz aus Audio-Port erkannt werden kann
  if( pauseFlash == true && abs(millis()-startPause)>90 ) {
     pauseFlash = false;
  }
  
  // Headphone Jack lesen
  sensorValue = analogRead(3);
  
  // Nur neue Blitze registrieren, wenn nicht abgeschaltet ist
  if( !pauseFlash ) {
   
    // Differenz aus letztem und aktuellem Wert
    diff = (int) abs( lastValue-sensorValue );
    
    // Diff überschritten
    if( diff > 20 && rec == false) {
        
        // start recording
        rec = true;
    
    // Auszeit zählen
    } else if( diff > 20 && rec == true) {
       
        // Counter hochzählen
          counter++;
        
    }
    
    if( counter > 30 ) {
  
      counter = 0; 
      rec = false;
      
      // Einen Flash in Queue einreihen
      flashQueue++;
      
      // Blitzregistrierung für 90ms pausieren
      pauseFlash = true;
      startPause = millis();
    }
    
  }
  
   // FlashQueue abarbeiten
  if( flashQueue > 0 && abs(millis()-flashPause)>pause ) {
    
    // Flash auslösen
    digitalWrite(0, HIGH); 
    
    // Queue runterzählen
    flashQueue--;
    
    // Zähler auslösen
    flashPause = millis();
  }
  
  // Blitzauslöser abschalten
  if( abs(millis()-flashPause)>duration ) {
    digitalWrite(0, LOW);
  }
   
  // Differenz aus letztem und aktuellem Wert
 // diff = (int) abs( lastValue-sensorValue );
  
  /*
  if( diff > 20 ) {
     digitalWrite(0, HIGH);
     digitalWrite(1, LOW);
     delay(50);
  } else {
     digitalWrite(0, LOW);
    digitalWrite(1, HIGH); 
  }
  */

  
  /*
  // Differenz über Zeit messen
  if( diff > 5 && counter < 50) {
     counter ++;
  } else if( diff < 5 && counter > 0 ) {
     counter --; 
  }
    
  
  if( counter > 30 ) {
     digitalWrite(0, HIGH);
     
     //for (int i = 0; i < 8; i++){
       if(servoState==1) {
       setServo(2);
       }
       //delay(100);
     //}
     
     // Serial.println("ON");
     // myServo.write(180);
  } else {
     digitalWrite(0, LOW);
     
     if(servoState==2) {
     setServo(1);
     }
     /*
     for (int i = 0; i < 8; i++){
       digitalWrite(1, HIGH);
       delay(2);
       digitalWrite(1, LOW);
       delay(20);
       //delay(100);
     }
     

     // Serial.println("OFF");
     // myServo.write(0); 
  }
  */
  
  
  lastValue = sensorValue;
  
}
