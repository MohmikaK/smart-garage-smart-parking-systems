#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
#define trigPin1 6
#define trigPin2 7
#define trigPin3 8
#define echoPin1 6
#define echoPin2 7
#define echoPin3 8
#define led1 0
#define led2 10
#define led3 13
#define buttonPin 1 // Pin for the push button
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool bool1 = false;
bool bool2 = false;
bool bool3 = false;

int pirPin = 1;                 
int pirStat = 0;                 
int pos = 0;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {

  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(pirPin, INPUT);
  myservo.attach(9); 
  lcd.begin(16, 2);
}

void loop() {
  
  
  
  float distance1 = (readUltrasonicDistance(trigPin1, echoPin1) * 0.034) / 2;
  float distance2 = (readUltrasonicDistance(trigPin2, echoPin2) * 0.034) / 2;
  float distance3 = (readUltrasonicDistance(trigPin3, echoPin3) * 0.034) / 2;

  // Check distances for each slot
  bool1 = distance1 < 320 && distance1 > 2;
  bool2 = distance2 < 320 && distance2 > 2;
  bool3 = distance3 < 320 && distance3 > 2;

  digitalWrite(led1, bool1 ? LOW : HIGH);
  digitalWrite(led2, bool2 ? LOW : HIGH);
  digitalWrite(led3, bool3 ? LOW : HIGH);
	
  pirStat = digitalRead(pirPin); 
  if (pirStat == HIGH) {  
   lcd.setCursor(0, 0);
   if (bool1 && bool2 && bool3) {
     lcd.print("Parking full");
     delay(2000);
   }
    else{
     lcd.print("Welcome!");
   
   for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);              
    delay(15);                       
   } 
     delay(2000);
    for (pos = 90; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
    }}
 } 
  
    // Display slot statuses if the button is not pressed
    lcd.setCursor(0, 0);

    if (!bool1 && !bool2 && !bool3) {
      lcd.print("All slots empty");
    } else if (bool1 && !bool2 && !bool3) {
      lcd.print("1 Slot filled");
      lcd.setCursor(0, 1);
      lcd.print("Slot 2 3 empty");
    } else if (!bool1 && bool2 && !bool3) {
      lcd.print("1 Slot filled");
      lcd.setCursor(0, 1);
      lcd.print("Slot 1 3 empty");
    } else if (bool1 && bool2 && !bool3) {
      lcd.print("2 Slot filled");
      lcd.setCursor(0, 1);
      lcd.print("Slot 3 empty");
    } else if (!bool1 && !bool2 && bool3) {
      lcd.print("1 Slot filled");
      lcd.setCursor(0, 1);
      lcd.print("Slot 1 2 empty");
    } else if (bool1 && !bool2 && bool3) {
      lcd.print("2 Slot filled");
      lcd.setCursor(0, 1);
      lcd.print("Slot 2 empty");
    } else if (!bool1 && bool2 && bool3) {
      lcd.print("2 Slot filled");
      lcd.setCursor(0, 1);
      lcd.print("Slot 1 empty");
    } else {
      lcd.print("All Slots filled");
    }
    delay(1000);
    lcd.clear();
  
}
