// buzzer and LED   // declare the ledPin as an OUTPUT:
const int buzzerPin = 7;
const int ledPin = 13;
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  // speed read here, with knob

int sensorPin = A0;    // select the input pin for the potentiometer
int adc = 0;
float sensorSpeed = 0;  // variable to store the value coming from the sensor
float speedKmph = 0;
float timeToHit = 0.0;
bool safe = 0;
//8 to echo
//9 to trig
//A0 mid
//ground to ground
//7 to buuzer to ground
//5 V to Vcc
//gnd to right
//Vcc to left

  // ultra sound distance sensing below
#define echoPin 8 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  // buzzer and LED   // declare the ledPin as an OUTPUT:
  pinMode(buzzerPin, OUTPUT);    
  pinMode(ledPin, OUTPUT);    

  lcd.begin(16,2);
  
  // speed read here, with knob
  
  
  
  // ultra sound distance sensing below
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {
  // speed read here, with knob  
    // read the value from the sensor:
  adc = analogRead(sensorPin);

  
  //sensorSpeed = 1000 * (90.0/90.0) * log10(1 * (1 + (adc / 1023.0))); 
  //speedKmph = 1 * (90.0/90.0) * log10(1 * (1 + (sensorSpeed / 1.0))); 
  speedKmph = (adc/1.0);  
  //Serial.print("Speed: ");
  //Serial.print(sensorSpeed/speedKmph);
  //Serial.print(" kilo meter per hour    ");

  
  
  // ultra sound distance sensing below  
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  
 float timeToHit = distance / (speedKmph * 1000.0 / 3600.0);                                                 ;
 // if (((speedKmph)*10*2)/36 > distance) {
 if ( timeToHit < 2.0) {
   //Serial.println("Buzz      |");
   digitalWrite(ledPin, HIGH);
   digitalWrite(buzzerPin, LOW);
   safe = 0;
   
 }
 else
 {
   digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, HIGH);
  safe = 1;
 }
  delay(100);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Speed:");
  lcd.setCursor(7,0);
  lcd.print(adc);
  lcd.setCursor(10,0);
  lcd.print("KMPH");
  lcd.setCursor(0,1);
  lcd.print("Distance:");
  lcd.setCursor(10,1);
  lcd.print(distance);
  lcd.setCursor(13,1);
  lcd.print("m");
  lcd.setCursor(15,0);
  lcd.print(safe);

  Serial.print("SpeedKmph:");
  //Serial.print(adc);
  //Serial.print("  ");
  //Serial.print(sensorSpeed);
  //Serial.print("  ");
  Serial.print(speedKmph);
  //Serial.print(((sensorSpeed/speedKmph)*10*2)/36);
  Serial.print(" Distance:");
  Serial.print(distance);
  Serial.print(" TimeToHit:");
  Serial.print(timeToHit);
  Serial.print(" Safe:");
  Serial.println(safe);
  delay(150);
  
}
