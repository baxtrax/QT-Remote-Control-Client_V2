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


void setup() {
  // put your setup code here, to run once:
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
}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(FR_ENA, 0);
  analogWrite(BL_ENA, 0);
  analogWrite(FL_ENA, 0);
  analogWrite(BR_ENA, 0);

  digitalWrite(FR_pin1, HIGH); // This is forward
  digitalWrite(FR_pin2, LOW);

  digitalWrite(BL_pin1, HIGH); // This is forward
  digitalWrite(BL_pin2, LOW);

  digitalWrite(FL_pin1, LOW);
  digitalWrite(FL_pin2, HIGH);

  digitalWrite(BR_pin1, HIGH);
  digitalWrite(BR_pin2, LOW);
  
}
