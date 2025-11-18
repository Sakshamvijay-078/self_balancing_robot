// Motor Test Code - Run this FIRST to verify motors and connections
// This code tests each motor independently

int ENA = 11;  // Left motor speed
int IN1 = 7;   // Left motor direction
int IN2 = 6;   // Left motor direction
int IN3 = 5;   // Right motor direction
int IN4 = 4;   // Right motor direction
int ENB = 10;  // Right motor speed

void setup() {
  Serial.begin(115200);
  
  // Set all pins as output
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Stop all motors
  stopAllMotors();
  
  Serial.println("Motor Test Started!");
  Serial.println("Make sure battery is connected to motor driver!");
  delay(2000);
}

void loop() {
  // Test 1: Left Motor Forward
  Serial.println("\n--- Test 1: Left Motor Forward (5 sec) ---");
  leftMotorForward(150);
  delay(5000);
  stopAllMotors();
  delay(1000);
  
  // Test 2: Left Motor Backward
  Serial.println("\n--- Test 2: Left Motor Backward (5 sec) ---");
  leftMotorBackward(150);
  delay(5000);
  stopAllMotors();
  delay(1000);
  
  // Test 3: Right Motor Forward
  Serial.println("\n--- Test 3: Right Motor Forward (5 sec) ---");
  rightMotorForward(150);
  delay(5000);
  stopAllMotors();
  delay(1000);
  
  // Test 4: Right Motor Backward
  Serial.println("\n--- Test 4: Right Motor Backward (5 sec) ---");
  rightMotorBackward(150);
  delay(5000);
  stopAllMotors();
  delay(1000);
  
  // Test 5: Both Motors Forward (Straight)
  Serial.println("\n--- Test 5: Both Motors Forward (5 sec) ---");
  leftMotorForward(150);
  rightMotorForward(150);
  delay(5000);
  stopAllMotors();
  delay(1000);
  
  // Test 6: Both Motors Backward (Straight Back)
  Serial.println("\n--- Test 6: Both Motors Backward (5 sec) ---");
  leftMotorBackward(150);
  rightMotorBackward(150);
  delay(5000);
  stopAllMotors();
  delay(1000);
  
  // Test 7: Speed Ramp
  Serial.println("\n--- Test 7: Speed Ramp - Left Motor (0 to 255) ---");
  for (int speed = 0; speed <= 255; speed += 10) {
    Serial.print("Speed: ");
    Serial.println(speed);
    leftMotorForward(speed);
    delay(300);
  }
  stopAllMotors();
  delay(1000);
  
  Serial.println("\n--- All Tests Complete ---");
  Serial.println("Press RESET button to run tests again");
  delay(10000); // Wait before repeating
}

// Left Motor Functions
void leftMotorForward(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  Serial.print("Left Forward - Speed: ");
  Serial.println(speed);
}

void leftMotorBackward(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  Serial.print("Left Backward - Speed: ");
  Serial.println(speed);
}

// Right Motor Functions
void rightMotorForward(int speed) {
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.print("Right Forward - Speed: ");
  Serial.println(speed);
}

void rightMotorBackward(int speed) {
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.print("Right Backward - Speed: ");
  Serial.println(speed);
}

// Stop all motors
void stopAllMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("All Motors Stopped");
}
