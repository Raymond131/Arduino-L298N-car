// Motor A connections
int enA = 9;
int in1 = 2;
int in2 = 3;
// Motor B connections
int enB = 6;
int in3 = 4;
int in4 = 5;
int chl2 = 21;//channel 2 pin, right hand vertical on the controller
int chl4 = 19;//channel 4 pin, left hand horizontal on the controller
int va2;
int va4;
int va2b;
int va4b;
int stickH = 1940;
int stickL = 1060;

int va2up = 1530, va2low = 1470;  //pwm upper and lower bounds for rounding off close-to-zero values
void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(chl2, INPUT);
  pinMode(chl4, INPUT);
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  Serial.begin(9600);
}

void loop() {
  va2 = pulseIn(chl2, HIGH, 25000);
  va4 = pulseIn(chl4, HIGH, 25000);//reading pwm ranging from 1000 to 2000 from flysky receiver
  
  //desensitize joystick and map pwm range to: -255 to 255
  if (va2 == 0 || (va2low < va2 && va2 < va2up)) va2b = 0;
  else {
    if (va2 >= va2up) {
      va2b = map(va2, va2up, stickH, 50, 255);
    } else va2b = map(va2, stickL, va2low, -255, -50);  // round off close to zero joystick values
  }

  if (va4 == 0 || (va2low < va4 && va4 < va2up)) va4b = 0;
  else {
    if (va4 >= va2up) {
      va4b = map(va4, va2up, stickH, 50, 255);
    } else va4b = map(va4, stickL, va2low, -255, -50);
  }

  // Serial.print(va4);
  // Serial.print(" va4, va4b");
  // Serial.print(va4b);
  // Serial.print("      ");
  // Serial.print(va2);
  // Serial.print(" va2, va2b");
  // Serial.println(va2b);

  arcadeDrive();
}

// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);

  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);

  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);
}

// Arcade drive with variable control(not on/off)
void arcadeDrive() {
  Serial.print(va2b);
  Serial.print("    ");
  Serial.print(va4b);
  Serial.print("        ");
  Serial.print(va2b-va4b);
  Serial.print("     ");
  Serial.println(va2b+ va4b);
  if (va2b - va4b > 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, va2b - va4b);
    
  } else {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, -(va2b - va4b));
  }

  if (va2b + va4b > 0) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, va2b + va4b);
  } else {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, -(va2b + va4b));
  }

  // Accelerate from zero to maximum speed
  // for (int i = 0; i < 256; i++) {
  // 	analogWrite(enA, i);
  // 	analogWrite(enB, i);
  // 	delay(20);
  // }

  // // Decelerate from maximum speed to zero
  // for (int i = 255; i >= 0; --i) {
  // 	analogWrite(enA, i);
  // 	analogWrite(enB, i);
  // 	delay(20);
  // }

  // Now turn off motors
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, LOW);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, LOW);
}

void tankDrive(){

}
