int hBridgeInput1 = 4;
int hBridgeInput2 = 2; 
int hBridgeInput3 = 7;
int hBridgeInput4 = 6;
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

struct Bead {
  int inputA;
  int inputB;
  int enablePin;
  dir currDir;
};

dir currDir = FORWARD;
void setDirection(dir newDir);

Bead bead1 = {hBridgeInput1, hBridgeInput2, speedPinA, FORWARD};
Bead bead2 = {hBridgeInput4, hBridgeInput3, speedPinB, FORWARD};

// Function definitions. The Arduino preprocessor apparently doesn't work correctly for
// custom-defined types?
// Perhaps more importantly, I switched to using a Bead* instead of just a Bead.
// http://alexpounds.com/blog/2016/01/10/using-structs-in-arduino-projects
//void flipBead(Bead bead);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < NUM_INPUTS; i++) {
    pinMode(hBridgeInput[i], OUTPUT);
  }
  pinMode(led, OUTPUT);
}

void testBead(dir newDir) {
  if (newDir == FORWARD) {
    
  }
}

void setDirectionNew(dir newDir) {
  if (newDir == FORWARD) {
    
  }
}

void setDirection(dir newDir) {
  if (newDir == FORWARD) {
    digitalWrite(led, HIGH);
    for (int i = 0; i < NUM_INPUTS; i++) {
      Serial.print("i: ");
      Serial.println(i);
      Serial.print("hBridgeInput[i]: ");
      Serial.println(hBridgeInput[i]);
      if (i%2 == 0) {
        digitalWrite(hBridgeInput[i], LOW);
      } else {
        digitalWrite(hBridgeInput[i], HIGH);
      } 
    }
  } else {
      digitalWrite(led, LOW);
      for (int i = 0; i < NUM_INPUTS; i++) {
        Serial.print("i: ");
      Serial.println(i);
      Serial.print("hBridgeInput[i]: ");
      Serial.println(hBridgeInput[i]);
        if (i%2 == 0) {
          digitalWrite(hBridgeInput[i], HIGH);
        } else {
          digitalWrite(hBridgeInput[i], LOW);
        }
      }
    }
}

void flipBead(Bead* bead) {
  Serial.println("flipping bead...");
  Serial.print("bead.currDir: ");
  Serial.println(bead->currDir);
  if (bead->currDir == FORWARD) {
    digitalWrite(bead->inputA, LOW);
    digitalWrite(bead->inputB, HIGH);
    bead->currDir = BACKWARD;
    Serial.print("was FORWARD, now: ");
    Serial.println(bead->currDir);
  } else {
    digitalWrite(bead->inputA, HIGH);
    digitalWrite(bead->inputB, LOW);
    bead->currDir = FORWARD;
    Serial.print("was BACKWARD, now: ");
    Serial.println(bead->currDir);
  }
  analogWrite(bead->enablePin, 200);
}

void loop() {

  Serial.print("bead1.inputA: ");
  Serial.println(bead1.inputA);
  Serial.print("bead1.inputB: ");
  Serial.println(bead1.inputB);
  Serial.print("bead2.inputA: ");
  Serial.println(bead2.inputA);
  Serial.print("bead2.inputB: ");
  Serial.println(bead2.inputB);
  Serial.print("bead1.enablePin: ");
  Serial.println(bead1.enablePin);
  Serial.print("bead2.enablePin: ");
  Serial.println(bead2.enablePin);
  Serial.print("bead1.currDir: ");
  Serial.println(bead1.currDir);
  Serial.print("bead2.currDir: ");
  Serial.println(bead2.currDir);

  Serial.print("currDir: ");
  Serial.println(currDir);
  
  if (currDir == FORWARD) {
    currDir = BACKWARD;
  } else {
    currDir = FORWARD;
  }
  
  //flipBead(&bead1);
  flipBead(&bead2);

  Serial.print("speedPinA: ");
  Serial.println(speedPinA);
  Serial.print("speedPinB: ");
  Serial.println(speedPinB);
  //setDirection(currDir);
  //analogWrite(speedPinA, 150);
  //analogWrite(speedPinB, 150);
  
  delay(3000);
  
  //plasma();
}

// Convenient 2D point structure
struct Point {
  float x;
  float y;
};

float phase = 0.0;
float phaseIncrement = 0.01;  // Controls the speed of the moving points. Higher == faster. I like 0.08 .
float colorStretch = 0.11;    // Higher numbers will produce tighter color bands. I like 0.11 .

float lastColor_1;
float lastColor_2;
float lastColor_3;

// This function is called every frame.
void plasma() {
  phase += phaseIncrement;
  
  // The two points move along Lissajious curves, see: http://en.wikipedia.org/wiki/Lissajous_curve
  // We want values that fit the LED grid: x values between 0..13, y values between 0..8 .
  // The sin() function returns values in the range of -1.0..1.0, so scale these to our desired ranges.
  // The phase value is multiplied by various constants; I chose these semi-randomly, to produce a nice motion.
  Point p1 = { (sin(phase*1.000)+1.0) * 4.5, (sin(phase*1.310)+1.0) * 4.0 };
  Point p2 = { (sin(phase*1.770)+1.0) * 4.5, (sin(phase*2.865)+1.0) * 4.0 };
  Point p3 = { (sin(phase*0.250)+1.0) * 4.5, (sin(phase*0.750)+1.0) * 4.0 };
  
  byte row, col;
  
  // For each row...
  for( row=0; row<8; row++ ) {
    float row_f = float(row);  // Optimization: Keep a floating point value of the row number, instead of recasting it repeatedly.
    
    // For each column...
    for( col=0; col<8; col++ ) {
      float col_f = float(col);  // Optimization.
      
      // Calculate the distance between this LED, and p1.
      Point dist1 = { col_f - p1.x, row_f - p1.y };  // The vector from p1 to this LED.
      float distance1 = sqrt( dist1.x*dist1.x + dist1.y*dist1.y );
      
      // Calculate the distance between this LED, and p2.
      Point dist2 = { col_f - p2.x, row_f - p2.y };  // The vector from p2 to this LED.
      float distance2 = sqrt( dist2.x*dist2.x + dist2.y*dist2.y );
      
      // Calculate the distance between this LED, and p3.
      Point dist3 = { col_f - p3.x, row_f - p3.y };  // The vector from p3 to this LED.
      float distance3 = sqrt( dist3.x*dist3.x + dist3.y*dist3.y );
      
      // Warp the distance with a sin() function. As the distance value increases, the LEDs will get light,dark,light,dark,etc...
      // You can use a cos() for slightly different shading, or experiment with other functions. Go crazy!
      float color_1 = distance1;  // range: 0.0...1.0
      float color_2 = distance2;
      float color_3 = distance3;
      float color_4 = (sin( distance1 * distance2 * colorStretch )) + 2.0 * 0.5;
      
      // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
      color_1 *= color_1 * color_4;
      color_2 *= color_2 * color_4;
      color_3 *= color_3 * color_4;
      color_4 *= color_4;
 
      // Scale the color up to 0..7 . Max brightness is 7.
      //strip.setPixelColor(col + (8 * row), strip.Color(color_4, 0, 0) );
      //strip.setPixelColor(col + (8 * row), strip.Color(color_1, color_2, color_3));
      Serial.print("color_1: ");
      Serial.println(color_1);
      Serial.print("color_2: ");
      Serial.println(color_2);
      Serial.print("color_3: ");
      Serial.println(color_3);

      if (triggerFlip(color_1, lastColor_1)) {
      //if (true) {
        flipBead(&bead1); 
      }

      lastColor_1 = color_1;
      lastColor_2 = color_2;
      lastColor_3 = color_3;
      delay(3000);
    }
  }
}

boolean triggerFlip(float newColor, float oldColor) {
  // if the difference is greater than some threshold
  return (abs(oldColor - newColor) > 8);
}

