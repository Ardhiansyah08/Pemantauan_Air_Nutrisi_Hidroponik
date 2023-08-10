int FloatSensor3 = 2;
int Buzzer = 9;
int buttonState3 = 1; //reads pushbutton status
void setup() {
  Serial.begin(9600);
  pinMode(FloatSensor3, INPUT_PULLUP);
  pinMode (Buzzer, OUTPUT);
}
void loop() {
  buttonState3 = digitalRead(FloatSensor3);
  if (buttonState3 == HIGH) {
    digitalWrite(Buzzer, LOW);
    Serial.println("WATER LEVEL - LOW");
  }
  else {
    digitalWrite(Buzzer, HIGH);
    Serial.println("WATER LEVEL - HIGH");
  }
  delay(1000);
}
