#include <Arduino.h>
#include <BleMouse.h>
#include <Wire.h>

const int MPU = 0x68;

// Create BLE mouse
BleMouse bleMouse("ESP32 AirMouse", "ESP32", 100);

// MPU6050 values
int16_t AcX, AcY, AcZ;

// Button pins
const int leftButton = 18;
const int rightButton = 19;
const int scrollUpButton = 23;
const int scrollDownButton = 5;

// Button states
bool lastLeft = false;
bool lastRight = false;

void setup() {

  Serial.begin(115200);

  // I2C start
  Wire.begin(21,22);

  // Wake MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Button setup
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(scrollUpButton, INPUT_PULLUP);
  pinMode(scrollDownButton, INPUT_PULLUP);

  // Start BLE mouse
  bleMouse.begin();
}

void loop() { 
  // Read MPU6050 accelerometer
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);

  AcX = Wire.read()<<8 | Wire.read();
  AcY = Wire.read()<<8 | Wire.read();
  AcZ = Wire.read()<<8 | Wire.read();

  Serial.print("X=");
  Serial.print(AcX);
  Serial.print(" Y=");
  Serial.print(AcY);
  Serial.print(" Z=");
  Serial.println(AcZ);

  if(bleMouse.isConnected()){

    // Cursor movement
    int xMove = AcX / 500;
    int yMove = AcY / 500;

    bleMouse.move(xMove, yMove);

    // Read buttons
    bool leftPressed = digitalRead(leftButton) == LOW;
    bool rightPressed = digitalRead(rightButton) == LOW;
    bool scrollUp = digitalRead(scrollUpButton) == LOW;
    bool scrollDown = digitalRead(scrollDownButton) == LOW;

    // Left click
    if(leftPressed && !lastLeft){
      bleMouse.press(MOUSE_LEFT);
    }
    if(!leftPressed && lastLeft){
      bleMouse.release(MOUSE_LEFT);
    }

    // Right click
    if(rightPressed && !lastRight){
      bleMouse.press(MOUSE_RIGHT);
    }
    if(!rightPressed && lastRight){
      bleMouse.release(MOUSE_RIGHT);
    }

    // Scroll up
    if(scrollUp){
      bleMouse.move(0,0,1);
    }

    // Scroll down
    if(scrollDown){
      bleMouse.move(0,0,-1);
    }

    lastLeft = leftPressed;
    lastRight = rightPressed;
  }

  delay(20);
}