#include <Servo.h>

Servo myservo;
const int photoPin = A0;
int threshold = 500;
unsigned long lastBlinkTime = 0;
int commandBits = 0;
int bitCount = 0;

void setup() {
  myservo.attach(9);
  pinMode(photoPin, INPUT);
}

void loop() {
  int lightLevel = analogRead(photoPin);
  unsigned long currentTime = millis();

  if (lightLevel < threshold) {
    if (currentTime - lastBlinkTime > 250) {
      lastBlinkTime = currentTime;
      bitCount++;
      
      if (currentTime - lastBlinkTime < 1000) {
        commandBits = commandBits << 1;
      } else {
        commandBits = (commandBits << 1) | 1;
      }
    }
  } else {
    if (currentTime - lastBlinkTime > 3000) {
      bitCount = 0;
      commandBits = 0;
    }
  }

  if (bitCount == 2) {
    int angle;
    switch (commandBits) {
      case 0: angle = 0; break;
      case 1: angle = 45; break;
      case 2: angle = 90; break;
      case 3: angle = 180; break;
    }
    myservo.write(angle);
    
    commandBits = 0;
    bitCount = 0;
  }
}
