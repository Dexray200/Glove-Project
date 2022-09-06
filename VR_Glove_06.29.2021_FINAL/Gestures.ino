//  Gesture for trigger
bool spiderGesture(int thumb, int index, int middle, int ring, int pinky){
  //  if ring and middle are less than 50%
  //  and all other 3 are above, it returns 1
  //  Else, it returns 0
  int half = 150 / 2;
  bool spider = 0;
  if(middle >= half && ring >= half && thumb <= half && index <= half && pinky <= half) {
    spider = 1;
  }
  else {
    spider = 0;
  }
  return spider;
}

//  Gesture for pinch
bool pinchGesture(int thumb, int index){
  //  If index and thumb are less than 50%, returns 1
  //  Else, returns 0
  return (thumb + index) / 2 <= (150 / 2) ? 0 : 1;
}

//  Gesture for grab
bool grabGesture(int thumb, int index, int middle, int ring){
  //  If all fingers are less than 50%
  return (thumb + index + middle + ring) / 4 <= (150 / 2) ? 0 : 1;
}

//  Gesture for peace Sign
bool peaceSign(int index, int middle, int ring, int pinky){
  //  If index and middle finger are less than 50%, returns 1,
  //  Else, returns 0
  int half = 150 / 2;
  bool peace = 0;
  if(index <= half && middle <= half && ring >= half){
    peace = 1;
  }
  else{
    peace = 0;
  }
  
  return peace;
}
