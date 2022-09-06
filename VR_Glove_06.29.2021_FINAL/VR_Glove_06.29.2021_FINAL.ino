///////////////////////////////////////////////////////
//   
//    ECE 405 - Summer 2021
//    VR Gloves Arduino Code
//    Date:   06.24.2021
//    Spencer Smith
//    Keri Henschen, Dexter Elmendorf, Mason Burt
//    
///////////////////////////////////////////////////////
#include <ArduinoBLE.h>
//#include <WiFiNINA.h>


//  IF YOU WISH TO USE BLE, SET TO TRUE.
//  ELSE, SET TO FALSE
bool bluetooth = true;
bool serial = true;
bool constCalibrationFinger = false;
bool constCalibrationSplay = true;


//  BLE Data Service
BLEService dataService("40510000-4786-42e7-bd27-45257b2e988f");
//  BLE LED Data Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic dataCharacteristic("40510001-4786-42e7-bd27-45257b2e988f", BLERead | BLENotify | BLEWrite);

//  Output of finger position MUX is connected to Arduino A0
const int fingerPos = A0;
//  Output of splay position MUX is connected to Arduino A1
const int splayPos = A1;

//  Three MUX Set pins for Finger Position are connected Arduino Digital 2, 3, and 4
const int s0 = 2;
const int s1 = 3;
const int s2 = 4;

//  Three MUX Set pins for Finger Splay are connected Arduino Digital 5, 6, and 7
const int s3 = 7;
const int s4 = 6;
const int s5 = 5;

//  xAxis and yAxis analog pins are connected to Arduino A2 and A3
const int xAxis = A2;
const int yAxis = A3;

//  Buttons A and B are conneted to Arduino Digital 8 and 9
const int buttonA = 8;
const int buttonB = 9;

//  Boolean variable for whether or not glove is calibrated
bool isCalibrated = false;

//  Declares min and max variables for each finger position
int min0, max0, min1, max1, min2, max2, min3, max3, min4, max4;
//  Declares a Calibrated min/max finger position array
int minMaxCal[10] = {min0,max0,min1,max1,min2,max2,min3,max3,min4,max4};

//  Declare min and max variables for each finger splay
int sMin0, sMax0, sMin1, sMax1, sMin2, sMax2, sMin3, sMax3, sMin4, sMax4;
//  Declares a calibrated min/max splay position array
int sMinMaxCal[10] = {sMin0,sMax0,sMin1,sMax1,sMin2,sMax2,sMin3,sMax3,sMin4,sMax4};

//  Empty array that stores the information to be sent through Serial
int encode[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  //  Begins serial communication
  Serial.begin(115200);
  //  Sets digital pins 8 and 9 to input mode
  pinMode(8, INPUT_PULLDOWN);
  pinMode(9, INPUT_PULLDOWN);
  pinMode(LED_BUILTIN, OUTPUT);

  //  Communicates trough Bluetooth if desired
  if(bluetooth == true){
    //  Begins BLE
    BLE.begin();
    //  Connects to host device
    BLE.setLocalName("HapDEX Gloves");
    BLE.setAdvertisedService(dataService);
    //  add the characteristic to the service
    dataService.addCharacteristic(dataCharacteristic);
    //  add service
    BLE.addService(dataService);
    //  start advertising
    BLE.advertise();
  }

  //  Set built-in LEDs for notification with Calibration
  //pinMode(LEDR, OUTPUT);
  //pinMode(LEDG, OUTPUT);
  //pinMode(LEDB, OUTPUT);
}

void loop() {
  //  If Calibration hasn't occurred, calls calibration() function
  if(isCalibrated == false){
    //  Waits 5 seconds
    delay(5000);
    
    //  Calls Calibration Function
    calibration();

    //  Sets global minimum and maximum values
    minMaxCal[0] = min0;
    minMaxCal[1] = min1;
    minMaxCal[2] = min2;
    minMaxCal[3] = min3;
    minMaxCal[4] = min4;
    minMaxCal[5] = max0;
    minMaxCal[6] = max1;
    minMaxCal[7] = max2;
    minMaxCal[8] = max3;
    minMaxCal[9] = max4;

    sMinMaxCal[0] = sMin0;
    sMinMaxCal[1] = sMin1;
    sMinMaxCal[2] = sMin2;
    sMinMaxCal[3] = sMin3;
    sMinMaxCal[4] = sMin4;
    sMinMaxCal[5] = sMax0;
    sMinMaxCal[6] = sMax1;
    sMinMaxCal[7] = sMax2;
    sMinMaxCal[8] = sMax3;
    sMinMaxCal[9] = sMax4;
    
    //  Sets isCalibrated to true
    isCalibrated = true;
  }

  //  Polls through the 5 different fingers to get values
  for(int i = 0; i < 5; i++){
    //  Calls muxSelect funtion to set the select pins High/Low
    muxSelect(i);

    //  Reads the current value for the finger currently in the chosen Channel
    int currentFinger = analogRead(fingerPos);

    //  Checks if the current value is bigger/smaller than the min/max
    //  If so, it adjusts the min/max accordingly
    if(constCalibrationFinger == true){
      if(currentFinger < minMaxCal[i]){
        minMaxCal[i] = currentFinger;
      }
      if(currentFinger > minMaxCal[i+5]){
        minMaxCal[i+5] = currentFinger;
      }
    }

    encode[i] = map((currentFinger - minMaxCal[i]), 0, minMaxCal[i+5], 0, 255);
    encode[i] = constrain(encode[i], 0, 255);

    //  MUST be a delay of 80
    //  Anything less is too fast for it to process adequately
    delay(15);
  }
  
  //  Polls through the 5 different fingers to get values
  for(int i = 0; i < 5; i++){
    //  Calls muxSelect funtion to set the select pins High/Low
    muxSelect(i);

    //  Reads the current value for Splay position
    int currentSplay = analogRead(splayPos);

    //  Checks if the current value is bigger/smaller than the min/max
    //  If so, it adjusts the min/max accordingly
    if(constCalibrationSplay == true){
      if(currentSplay < sMinMaxCal[i]){
        sMinMaxCal[i] = currentSplay;
      }
      if(currentSplay > sMinMaxCal[i+5]){
        sMinMaxCal[i+5] = currentSplay;
      }
    }

    encode[i+5] = map((currentSplay - sMinMaxCal[i]), 0, sMinMaxCal[i+5], 0, 255);
    encode[i+5] = constrain(encode[i+5], 0, 255);

    delay(15);
  }

  //  Inserts the values of the xAxis and yAxis of the analog thumb stick into the array
  //  NOTE: min/max values are from experimental testing of that specific thumb stick
  encode[10] = map(analogRead(xAxis), 145, 550, 0, 255);
  encode[11] = map(analogRead(yAxis), 545, 860, 0, 255);
  //  Inserts the values of the two buttons into the array
  encode[12] = digitalRead(buttonA);
  encode[13] = digitalRead(buttonB);
  //  Inserts the values of the gestures
  encode[14] = spiderGesture(encode[0], encode[1], encode[2], encode[3], encode[4]);
  encode[15] = pinchGesture(encode[0], encode[1]);
  encode[16] = grabGesture(encode[0], encode[1], encode[2], encode[3]);
  encode[17] = peaceSign(encode[1], encode[2], encode[3], encode[4]);

  //  Encodes the array encode[] into a string to be sent to the PC
  if(serial == true){
    serialEncode();
    Serial.print('\n');
  }

  if(bluetooth == true){
    for(int i = 0; i < 18; i++){
      // listen for BLE peripherals to connect:
      BLEDevice central = BLE.central();
      // if a central is connected to peripheral:
      //Serial.print("Connected to central: ");
      // print the central's MAC address:
      //Serial.println(central.address());
      // while the central is still connected to peripheral:
      if (central.connected()) {
      dataCharacteristic.writeValue(encode[i]); //write gyro data into ble characteristic
    }
    //Serial.println(dataCharacteristic.value());
    }
  }
}
