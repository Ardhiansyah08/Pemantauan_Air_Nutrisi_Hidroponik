#include <EEPROM.h>
#include <GravityTDS.h>
#include <LiquidCrystal_I2C.h>

#define TdsSensorPin A0
GravityTDS gravityTds;
float tdsValue=0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Deklarasi LED
int LEDPin1 = 13;
int LEDPin2 = 12;

//Deklarasi Float water level sensor
int FloatSensor1 = 7;
int FloatSensor2 = 4;
int FloatSensor3 = 2;
int Relay1 = 6;
int Relay2 = 10;
int Relay3 = 5;
int Relay4 = 3;
int Buzzer = 9;
int buttonState1 = 1; //reads pushbutton status
int buttonState2 = 1;
int buttonState3 = 1;


void setup(){
  Serial.begin(115200);
  
//  LCD  
  lcd.begin(16, 2);
  lcd.backlight();
  
//  Gravity TDS Meter 
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
  
//  Deklarasikan pin Mode
  pinMode (FloatSensor1, INPUT_PULLUP);
  pinMode (FloatSensor2, INPUT_PULLUP);
  pinMode (FloatSensor3, INPUT_PULLUP);
  pinMode (Relay1, OUTPUT);
  pinMode (Relay2, OUTPUT);
  pinMode (Relay3, OUTPUT);
  pinMode (Relay4, OUTPUT);
  pinMode (LEDPin1, OUTPUT);
  pinMode (LEDPin2, OUTPUT);
  pinMode (Buzzer, OUTPUT);
          
}

void loop(){
//  gravityTds.setTemperature(temperature);
  gravityTds.update();  //sample and calculate
  tdsValue = gravityTds.getTdsValue();  // then get the value
  Serial.print(tdsValue, 0);
  Serial.println("ppm");
  lcd.setCursor(0, 0);
  lcd.print("TDS Value:");
  lcd.setCursor(0, 1);
  lcd.print(tdsValue,0);
  lcd.print("PPM");
  delay(1000);
  lcd.clear();

//  Kondisi sensor TDS-LED-Pompa
  if (tdsValue <= 560){
    digitalWrite(LEDPin1, HIGH);
    digitalWrite(LEDPin2, LOW);
    digitalWrite(Relay3, LOW);
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay4, HIGH);//Kondisi nyala air murni
  }
  else if (tdsValue >= 840){
    digitalWrite(LEDPin1, HIGH);
    digitalWrite(LEDPin2, LOW);
    digitalWrite(Relay4, LOW);
    digitalWrite(Relay3, HIGH);
    digitalWrite(Relay2, HIGH);
  }
  else {
    digitalWrite(LEDPin2, HIGH);
    digitalWrite(LEDPin1, LOW);
    digitalWrite(Relay2, HIGH);
    digitalWrite(Relay3, HIGH);
    digitalWrite(Relay4, HIGH);
  }

//  Kondisi float sensor (penampung 1)
 buttonState1 = digitalRead(FloatSensor1);
 buttonState2 = digitalRead(FloatSensor2);
  if (buttonState1 == LOW) {
    digitalWrite(Relay1, LOW);
    Serial.println("WATER LEVEL - LOW");
  }
  else if (buttonState2 == HIGH) {
    digitalWrite(Relay1, HIGH);
  }

//  Kondisi Sensor Float 3 (penampung 2)
  buttonState3 = digitalRead(FloatSensor3);
  if (buttonState3 == HIGH) {
    digitalWrite(Buzzer, LOW);
    Serial.println("WATER LEVEL - HIGH");
  }
  else {
    digitalWrite(Buzzer, HIGH);
    Serial.println("WATER LEVEL - LOW");
  }
}
