int hBridgeInput1 = 4;
int hBridgeInput2 = 2; // white
int speedPinA = 3; // Needs to be a PWM pin to be able to control motor speed.
int led = 13;
enum dir {
  FORWARD,
  BACKWARD
};
int currDir = FORWARD;
void setDirection(dir newDir);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(hBridgeInput1, OUTPUT);
  pinMode(hBridgeInput2, OUTPUT);
  pinMode(led, OUTPUT);
}
void setDirection(dir newDir) {
  if (newDir == FORWARD) {
    //Serial.println("Forward");
    digitalWrite(hBridgeInput1, LOW);
    digitalWrite(hBridgeInput2, HIGH);
    digitalWrite(led, HIGH);
  } else {
    //Serial.println("Backward");
    digitalWrite(hBridgeInput1, HIGH);
    digitalWrite(hBridgeInput2, LOW);
    digitalWrite(led, LOW);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
   if (currDir == FORWARD) {
    currDir = BACKWARD;
  } else {
    currDir = FORWARD;
  }
  Serial.print("currDir:");
  Serial.println(currDir);
  setDirection(currDir);
  analogWrite(speedPinA, 100);
  delay(5000);
}
