
int FR_pin1 = 12;
int FR_pin2 = 13;
int FR_ENA = 11;

int BL_pin1 = 3;
int BL_pin2 = 2;
int BL_ENA = 5;

int FL_pin1 = 8;
int FL_pin2 = 9;
int FL_ENA = 10;

int BR_pin1 = 7;
int BR_pin2 = 4;
int BR_ENA = 6;


const byte numChars = 100; // Size of packets (needs to be tuned)
const char startMarker = '<';
const char endMarker = '>';
char receivedChars[numChars];
char tempChars[numChars];

float FLSpeed = 0;
float FRSpeed = 0;
float BLSpeed = 0;
float BRSpeed = 0;

boolean newData = false;

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.write("Data Setup");
  // Initialize serial port to send and receive at 9600 baud
  pinMode(FR_pin1, OUTPUT);
  pinMode(FR_pin2, OUTPUT);
  pinMode(FR_ENA, OUTPUT);

  pinMode(BL_pin1, OUTPUT);
  pinMode(BL_pin2, OUTPUT);
  pinMode(BL_ENA, OUTPUT);

  pinMode(FL_pin1, OUTPUT);
  pinMode(FL_pin2, OUTPUT);
  pinMode(FL_ENA, OUTPUT);

  pinMode(BR_pin1, OUTPUT);
  pinMode(BR_pin2, OUTPUT);
  pinMode(BR_ENA, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  analogWrite(FR_ENA, 0);
  digitalWrite(FR_pin1, LOW);
  digitalWrite(FR_pin2, LOW);

  analogWrite(BL_ENA, 0);
  digitalWrite(BL_pin1, LOW);
  digitalWrite(BL_pin2, LOW);

  analogWrite(FL_ENA, 0);
  digitalWrite(FL_pin1, LOW);
  digitalWrite(FL_pin2, LOW);

  analogWrite(BR_ENA, 0);
  digitalWrite(BR_pin1, LOW);
  digitalWrite(BR_pin2, LOW);

}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {      // split the data into its parts
  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars,",");
  
  FRSpeed = atof(strtokIndx);
 
  strtokIndx = strtok(NULL, ",");
  BLSpeed = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  FLSpeed = atof(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");
  BRSpeed = atof(strtokIndx); 

}

void sendSpeedsToMotors() {
  //Serial.println(String(FRSpeed) + " " + String(BLSpeed) + " " + String(FLSpeed) + " " + String(BRSpeed));
  
  if(FRSpeed > 0) {             //FORWARD
    analogWrite(FR_ENA, (int)(abs(FRSpeed)*255.999));
    digitalWrite(FR_pin1, LOW);
    digitalWrite(FR_pin2, HIGH);
  } else if (FRSpeed < 0) {     //REVERSE
    analogWrite(FR_ENA, (int)(abs(FRSpeed)*255.999));
    digitalWrite(FR_pin1, HIGH);
    digitalWrite(FR_pin2, LOW);
  } else {                      //STOP
    analogWrite(FR_ENA, 255);
    digitalWrite(FR_pin1, LOW);
    digitalWrite(FR_pin2, LOW);
  }

  if(BLSpeed > 0) {             //FORWARD
    analogWrite(BL_ENA, (int)(abs(BLSpeed)*255.999));
    digitalWrite(BL_pin1, HIGH);
    digitalWrite(BL_pin2, LOW);
  } else if (BLSpeed < 0) {     //REVERSE
    analogWrite(BL_ENA, (int)(abs(BLSpeed)*255.999));
    digitalWrite(BL_pin1, LOW);
    digitalWrite(BL_pin2, HIGH);
  } else {                      //STOP
    analogWrite(BL_ENA, 255);
    digitalWrite(BL_pin1, LOW);
    digitalWrite(BL_pin2, LOW);
  }

  if(FLSpeed > 0) {             //FORWARD
    analogWrite(FL_ENA, (int)(abs(FLSpeed)*255.999));
    digitalWrite(FL_pin1, LOW);
    digitalWrite(FL_pin2, HIGH);
  } else if (FLSpeed < 0) {     //REVERSE
    analogWrite(FL_ENA, (int)(abs(FLSpeed)*255.999));
    digitalWrite(FL_pin1, HIGH);
    digitalWrite(FL_pin2, LOW);
  } else {                      //STOP
    analogWrite(FL_ENA, 255);
    digitalWrite(FL_pin1, LOW);
    digitalWrite(FL_pin2, LOW);
  }

  if(BRSpeed > 0) {             //FORWARD
    analogWrite(BR_ENA, (int)(abs(BRSpeed)*255.999));
    digitalWrite(BR_pin1, HIGH);
    digitalWrite(BR_pin2, LOW);
  } else if (BRSpeed < 0) {     //REVERSE
    analogWrite(BR_ENA, (int)(abs(BRSpeed)*255.999));
    digitalWrite(BR_pin1, LOW);
    digitalWrite(BR_pin2, HIGH);
  } else {                      //STOP
    analogWrite(BR_ENA, 255);
    digitalWrite(BR_pin1, LOW);
    digitalWrite(BR_pin2, LOW);
  }
}

void loop()
{
  // Set the speed in steps per second:
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    newData = false;
  }
  sendSpeedsToMotors();
}
