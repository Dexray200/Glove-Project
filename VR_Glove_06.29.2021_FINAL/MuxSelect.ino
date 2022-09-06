///////////////////////////////////////////////
//
//  Function to set Multiplexer Select Pins
//
///////////////////////////////////////////////

void muxSelect(int digit){
  //  digit = 0 for thumb, digit = 4 for pinky
  //  Writes digital pins Low/High to select correct channel
  switch(digit){
    case 0:
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);

      digitalWrite(s3, LOW);
      digitalWrite(s4, LOW);
      digitalWrite(s5, LOW);
      break;
    case 1:
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);

      digitalWrite(s3, HIGH);
      digitalWrite(s4, LOW);
      digitalWrite(s5, LOW);
      break;  
    case 2:
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);

      digitalWrite(s3, LOW);
      digitalWrite(s4, HIGH);
      digitalWrite(s5, LOW);
      break; 
    case 3:
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);

      digitalWrite(s3, HIGH);
      digitalWrite(s4, HIGH);
      digitalWrite(s5, LOW);
      break; 
    case 4:
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);

      digitalWrite(s3, LOW);
      digitalWrite(s4, LOW);
      digitalWrite(s5, HIGH);
      break;    
  }
  return;
}
