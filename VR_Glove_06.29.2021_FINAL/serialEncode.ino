void serialEncode(){
  String communication;
  for(int i = 0; i < 18; i++){
    communication.concat(encode[i]);
    if(i < 17){
      communication.concat("&");
    }
  }
  if(serial == true){
    Serial.print(communication);
  }
}
