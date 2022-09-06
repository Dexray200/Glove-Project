///////////////////////////////////////////////
//
//  Function to Calibrate Finger Max/Min Positions
//
///////////////////////////////////////////////
void calibration(){
  int fingerMinPosition[5];
  int fingerMaxPosition[5];
  int sFingerMin[5];
  int sFingerMax[5];
  
  //  Tells user to open hand completely
  if(serial == true){
    Serial.write("Open hand completely");
    Serial.write('\n');
  }
  //  Turns red LED on to tell user to open hand
  digitalWrite(LED_BUILTIN, HIGH);
  
  //  Waits 5 seconds for user to open hand
  delay(5000);
  
    //  Takes analog read for each finger position
    for(int i = 0; i < 5; i++){
      muxSelect(i);
      fingerMinPosition[i] = analogRead(fingerPos);
      delay(30);
    }
    
    //  Turns Red LED off, and Idle Green LED ON
    if(serial == true){
      //digitalWrite(LEDR, LOW);
      //digitalWrite(LEDG, HIGH);
    }
    //  Waits 1 second
    delay(1000);
    
  //  Prints minimum values for verification purposes
  if(serial == true){
    Serial.write("Minimum Values:");
    Serial.write('\n');
    for(int j = 0; j < 5; j++){
      Serial.print(fingerMinPosition[j]);
    Serial.print("  ");
    }
    Serial.print('\n');
  }
  
  //  Asks user to close hand completely for 5 seconds
  if(serial == true){
    Serial.write("Close Hand Completely for 5 Seconds");
    Serial.write('\n');
  }
  //  Turns Green LED off, and BLUE LED ON to tell user to close hand
  digitalWrite(LED_BUILTIN, LOW);
  //digitalWrite(LEDB, HIGH);
  //  Waits 5 seconds
  delay(5000);
  
    //  Takes analog reading for each finger position
    for(int i = 0; i < 5; i++){
      muxSelect(i);
      fingerMaxPosition[i] = analogRead(fingerPos);
      delay(30);
    }
    
    //  Turns blue LED off and Green LED on
    //digitalWrite(LEDB, LOW);
    //digitalWrite(LEDG, HIGH);
    //  Waits 1 second
    delay(1000);
    
  //  Prints maximum values for verficiation purposes
  if(serial == true){
    Serial.write("Maximum Values:");
    Serial.write('\n');
    for(int j = 0; j < 5; j++){
      Serial.print(fingerMaxPosition[j]);
      Serial.print("  ");
    }
    Serial.print('\n');
  }
  
  //  SPLAY MINIMUM
  if(serial == true){
    Serial.write("Close Splay Completely");
    Serial.write('\n');
    //  Turns Green LED off and RED LED on to tell user to close splay
  }
  //digitalWrite(LEDG, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  //  Waits 5 seconds
  delay(5000);
  
  //  Takes analog read for each finger position
  for(int i = 0; i < 5; i++){
     muxSelect(i);
     sFingerMin[i] = analogRead(splayPos);
     delay(30);
  }
  //  Turns blue LED off and Green LED On
  //digitalWrite(LEDB, LOW);
  //digitalWrite(LEDG, HIGH);
  //  Waits 1 second
  delay(1000);
  
  //  Prints minimum values for verification purposes
  if(serial == true){
    Serial.write("Minimum Values:");
    Serial.write('\n');
    for(int j = 0; j < 5; j++){
      Serial.print(sFingerMin[j]);
      Serial.print("  ");
    }
    Serial.print('\n');
  }
  
  //  SPLAY MAXIMUM
  if(serial == true){
    Serial.write("Open Splay Completely");
    Serial.write('\n');
  }

  //  Turns green LED off and Blue LED on to tell user to open splay
  digitalWrite(LED_BUILTIN, LOW);
  //digitalWrite(LEDB, HIGH);
  //  Waits 5 seconds
  delay(5000);
  
  //  Takes analog read for each finger position
  for(int i = 0; i < 5; i++){
     muxSelect(i);
     sFingerMax[i] = analogRead(splayPos);
     delay(30);
  }

  //  Turns blue LED off and Green LED ON
  //digitalWrite(LEDB, LOW);
  //digitalWrite(LEDG, HIGH);
  //  Waits 1 second
  delay(1000);
  
  //  Prints minimum values for verification purposes
  if(serial == true){
    Serial.write("Maximum Values:");
    Serial.write('\n');
    for(int j = 0; j < 5; j++){
      Serial.print(sFingerMax[j]);
      Serial.print("  ");
    }
    Serial.print('\n');
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  //  Sets each min/max global varaible to their min/max
  min0 = fingerMinPosition[0];
  min1 = fingerMinPosition[1];
  min2 = fingerMinPosition[2];
  min3 = fingerMinPosition[3];
  min4 = fingerMinPosition[4];
  max0 = fingerMaxPosition[0];
  max1 = fingerMaxPosition[1];
  max2 = fingerMaxPosition[2];
  max3 = fingerMaxPosition[3];
  max4 = fingerMaxPosition[4];

  sMin0 = sFingerMin[0];
  sMin1 = sFingerMin[1];
  sMin2 = sFingerMin[2];
  sMin3 = sFingerMin[3];
  sMin4 = sFingerMin[4];
  sMax0 = sFingerMax[0];
  sMax0 = sFingerMax[1];
  sMax0 = sFingerMax[2];
  sMax0 = sFingerMax[3];
  sMax0 = sFingerMax[4];
        
  
  return;
}
