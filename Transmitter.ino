const int potPin = A0;
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  Serial.print("Potentiometer Value: "); Serial.println(potValue);

  int command = map(potValue, 0, 1023, 0, 3);

  Serial.print("Command: "); Serial.println(command);

  for (int i = 1; i >= 0; --i) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay((command & (1 << i)) ? 1000 : 250);
  }
  
  delay(3000);
}
