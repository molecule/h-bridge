int hBridgeInput1 = 4;
int hBridgeInput2 = 2; 
int hBridgeInput4 = 6;
int hBridgeInput3 = 7;
int speedPinA = 3; // Needs to be a PWM pin to be able to control motor speed.
int speedPinB = 5;
int led = 13;

#define NUM_INPUTS 4
int hBridgeInput[NUM_INPUTS] = {
  4, 2, 6, 7
};

enum dir {
  FORWARD,
  BACKWARD
};
int currDir = FORWARD;
void setDirection(dir newDir);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < NUM_INPUTS; i++) {
    pinMode(hBridgeInput[i], OUTPUT);
  }
  pinMode(led, OUTPUT);
}

void setDirection(dir newDir) {
  if (newDir == FORWARD) {
    digitalWrite(led, HIGH);
    for (int i = 0; i < NUM_INPUTS; i++) {
      if (i%2 == 0) {
        digitalWrite(hBridgeInput[i], LOW);
      } else {
        digitalWrite(hBridgeInput[i], HIGH);
      } 
    }
  } else {
      digitalWrite(led, LOW);
      for (int i = 0; i < NUM_INPUTS; i++) {
        if (i%2 == 0) {
          digitalWrite(hBridgeInput[i], HIGH);
        } else {
          digitalWrite(hBridgeInput[i], LOW);
        }
      }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
   if (currDir == FORWARD) {
    currDir = BACKWARD;
  } else {
    currDir = FORWARD;
  }
  Serial.print("currDir: ");
  Serial.println(currDir);
  setDirection(currDir);
  analogWrite(speedPinA, 150);
  analogWrite(speedPinB, 150);
  delay(3000);
}
