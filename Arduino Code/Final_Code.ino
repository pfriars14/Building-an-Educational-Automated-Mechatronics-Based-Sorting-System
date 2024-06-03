#include <Servo.h>

// Variables, definitions, etc..
unsigned long GetTimeNowMilli(void);
unsigned long GetTimeNowMicro(void);



// HopperTask
void HopperTask(void);
#define HopperActuatorPin 13
byte HopperState;
byte HopperNextState;
byte HopperState1Entry;
byte HopperState2Entry;
byte HopperState3Entry;
byte HopperState4Entry;
Servo servo4;
unsigned long HopperStartTime1 = 0;
unsigned long HopperStartTime2 = 0;
unsigned long HopperStartTime3 = 0;
unsigned long HopperStartTime4 = 0;



//Servo Task
void ServoTask(void);
byte ServoState;
byte ServoNextState;
byte ServoState1Entry;
byte ServoState2Entry;
byte ServoState3Entry;
byte ServoState4Entry;
unsigned long ServoStartTime1 = 0;
unsigned long ServoStartTime2 = 0;
unsigned long ServoStartTime3 = 0;
// int angle = 0;
Servo servo1;
Servo servo2;
Servo servo3;


// Stepper Task
void StepperMotorTask(void);
byte StepperState;
byte StepperNextState;
byte StepperState1Entry;
byte StepperState2Entry;
unsigned long StepperStartTime1 = 0;
unsigned long StepperStartTime2 = 0;
int StepPulse = 3;
int StepDir = 2;


//Color Sensor Task
void ColorSensorTask();
byte ColorState;
byte ColorNextState;
byte ColorState1Entry;
byte ColorState2Entry;
byte ColorState3Entry;
unsigned long ColorStartTime1 = 0;
unsigned long ColorStartTime2 = 0;
unsigned long ColorStartTime3 = 0;
int frequency = 0;
int color = 0;
int Rf = 0;
int Gf = 0;
int Bf = 0;
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 12


void setup() {

  // Misc.
  Serial.begin(9600);

  // Hopper Task
  pinMode(HopperActuatorPin, OUTPUT);
  HopperState1Entry = false;
  HopperState2Entry = false;
  HopperState3Entry = false;
  HopperState4Entry = false;
  servo4.attach(8);

  // Servo Task
  ServoState1Entry = false;
  ServoState2Entry = false;
  ServoState3Entry = false;
  ServoState4Entry = false;
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);


  //Color Sensor Task
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  ColorState1Entry = false;
  ColorState2Entry = false;
  ColorState3Entry = false;


  // Stepper Task
  pinMode(StepPulse, OUTPUT);
  pinMode(StepDir, OUTPUT);
  digitalWrite(StepDir, LOW);
  StepperState1Entry = false;
  StepperState2Entry = false;
}





void loop() {

  StepperNextState = 1;
  ColorNextState = 1;
  ServoNextState = 1;
  HopperNextState = 1;

  while (2 > 1) {
    HopperTask();
    ServoTask();
    StepperMotorTask();
    ColorSensorTask();
    // Serial.println(color);
  }
}





void HopperTask(void) {
  HopperState = HopperNextState;

  switch (HopperState) {

    case 1:

      if (HopperState1Entry == false) {
        servo4.write(300);
        digitalWrite(HopperActuatorPin, LOW);
        HopperStartTime1 = GetTimeNowMilli();
        HopperState1Entry = true;
      }
      if (GetTimeNowMilli() - HopperStartTime1 >= 5000){
        HopperState1Entry = false;
        HopperNextState = 2;
      }
      break;


    case 2:

      if (HopperState2Entry == false) {
        // servo4.write(300);
        digitalWrite(HopperActuatorPin, HIGH);
        HopperStartTime2 = GetTimeNowMilli();
        HopperState2Entry = true;
      }
      if (GetTimeNowMilli() - HopperStartTime2 >= 300){
        HopperState2Entry = false;
        HopperNextState = 3;
      }
      break;


    case 3:

      if (HopperState3Entry == false) {
        servo4.write(0);
        // digitalWrite(HopperActuatorPin, HIGH);
        HopperStartTime3 = GetTimeNowMilli();
        HopperState3Entry = true;
      }
      if (GetTimeNowMilli() - HopperStartTime3 >= 2000){
        HopperState3Entry = false;
        HopperNextState = 4;
      }
      break;


    case 4:

      if (HopperState4Entry == false) {
        servo4.write(300);
        // digitalWrite(HopperActuatorPin, HIGH);
        HopperStartTime4 = GetTimeNowMilli();
        HopperState4Entry = true;
      }
      if (GetTimeNowMilli() - HopperStartTime4 >= 750){
        HopperState4Entry = false;
        HopperNextState = 1;
      }
      break;
  }
}




void ServoTask(void) {
  ServoState = ServoNextState;
  switch (ServoState) {
    case 1:

      if (ServoState1Entry == false) {
        servo1.write(0);
        servo2.write(0);
        servo3.write(0);
        ServoState1Entry = true;
      }
      if (color == 1) {
        ServoNextState = 2;
        ServoState1Entry = false;
      }
      if (color == 2) {
        ServoNextState = 3;
        ServoState1Entry = false;
      }
      if (color == 3) {
        ServoNextState = 4;
        ServoState1Entry = false;
      }
      break;

    case 2:
      if (ServoState2Entry == false) {
        servo1.write(45);
        servo2.write(0);
        servo3.write(0);
        ServoStartTime1 = GetTimeNowMilli();
        ServoState2Entry = true;
      }
      if (GetTimeNowMilli() - ServoStartTime1 >= 5000) {
        ServoState2Entry = false;
        ServoNextState = 1;
        color = 0;
      }
      break;

    case 3:
      if (ServoState3Entry == false) {
        servo1.write(0);
        servo2.write(52);
        servo3.write(0);
        ServoStartTime2 = GetTimeNowMilli();
        ServoState3Entry = true;
      }
      if (GetTimeNowMilli() - ServoStartTime2 >= 5000) {
        ServoState3Entry = false;
        ServoNextState = 1;
        color = 0;
      }
      break;

    case 4:
      if (ServoState4Entry == false) {
        servo1.write(0);
        servo2.write(0);
        servo3.write(47);
        ServoStartTime3 = GetTimeNowMilli();
        ServoState4Entry = true;
      }
      if (GetTimeNowMilli() - ServoStartTime3 >= 5000) {
        ServoState4Entry = false;
        ServoNextState = 1;
        color = 0;
      }
      break;
  }
}







void StepperMotorTask(void) {

  StepperState = StepperNextState;

  // Serial.println(StepperState);

  switch (StepperState) {
    case 1:

      if (StepperState1Entry == false) {
        digitalWrite(StepPulse, HIGH);
        StepperStartTime1 = GetTimeNowMicro();
        StepperState1Entry = true;
      }
      if (GetTimeNowMicro() - StepperStartTime1 >= 407) {
        StepperState1Entry = false;
        StepperNextState = 2;
      }

      break;

    case 2:
      if (StepperState2Entry == false) {
        digitalWrite(StepPulse, LOW);
        StepperStartTime2 = GetTimeNowMicro();
        StepperState2Entry = true;
      }
      if (GetTimeNowMicro() - StepperStartTime2 >= 407) {
        StepperState2Entry = false;
        StepperNextState = 1;
      }
      break;
  }
}




void ColorSensorTask(void) {
  ColorState = ColorNextState;



  switch (ColorState) {
    case 1:

      if (ColorState1Entry == false) {
        digitalWrite(S2, LOW);
        digitalWrite(S3, LOW);
        Rf = pulseIn(sensorOut, LOW);
        ColorStartTime1 = GetTimeNowMilli();
        ColorState1Entry = true;
      }
      if (GetTimeNowMilli() - ColorStartTime1 >= 10) {
        ColorState1Entry = false;
        ColorNextState = 2;
      }

      break;

    case 2:
      if (ColorState2Entry == false) {
        digitalWrite(S2, HIGH);
        digitalWrite(S3, HIGH);
        Gf = pulseIn(sensorOut, LOW);

        ColorStartTime2 = GetTimeNowMilli();
        ColorState2Entry = true;
      }
      if (GetTimeNowMilli() - ColorStartTime2 >= 10) {
        ColorState2Entry = false;
        ColorNextState = 3;
      }
      break;

    case 3:
      if (ColorState3Entry == false) {
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        // Reading the output frequency
        Bf = pulseIn(sensorOut, LOW);

        if (Rf<25 & Rf>15 & Gf<40 & Gf>33 & Bf<40 & Bf>30) {
          color = 2; //Red
        }
        if (Rf<60 & Rf>40 & Gf<40 & Gf>20 & Bf<30 & Bf>10) {
          color = 1; //Blue
        }
        if (Rf<30 & Rf>20 & Gf<23 & Gf>10 & Bf<30 & Bf>20) {
          color = 3; //Green
        }
        if (Rf < 53 && Rf > 44 && Gf < 51 && Gf > 47 && Bf < 48 && Bf > 43) {
          color = 0;
        }
        ColorStartTime3 = GetTimeNowMilli();
        ColorState3Entry = true;
      }
      if (GetTimeNowMilli() - ColorStartTime3 >= 10) {
        ColorState3Entry = false;
        ColorNextState = 1;
      }
      break;
  }
}



// Timers

unsigned long GetTimeNowMilli(void) {
  return (millis());
}


unsigned long GetTimeNowMicro(void) {
  return (micros());
}