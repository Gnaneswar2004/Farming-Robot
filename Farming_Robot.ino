#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3SC2pCr2K"
#define BLYNK_TEMPLATE_NAME "Farming robot"
#define BLYNK_AUTH_TOKEN "MwvnwIocVe2bLEnUGHz2X_tnBnkLNHSl"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Define the motor pins
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D5
#define ENB D6

// Variables for the Blynk widget values
int x = 50;
int y = 50;
int Speed;
int pos1;
Servo servo1;
Servo servo2;
int servoPin1 = D4;  // Choose a free GPIO pin for the servo
int servoPin2 = D7;
int servoPosition1 = 90;  // Initialize the servo to the middle position (90 degrees)

char auth[] = "MwvnwIocVe2bLEnUGHz2X_tnBnkLNHSl"; //Enter your Blynk auth token
char ssid[] = "Gnani"; //Enter your WIFI name
char pass[] = "Gnani2004$"; //Enter your WIFI passowrd

void setup() {
  Serial.begin(9600);
  //Set the motor pins as output pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(servoPosition1);  // Set the initial servo position 

  // Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

// Get the joystick values
BLYNK_WRITE(V0) {
  x = param[0].asInt();
}
// Get the joystick values
BLYNK_WRITE(V1) {
  y = param[0].asInt();
}
//Get the slider values
BLYNK_WRITE(V2) {
  Speed = param.asInt();
}
BLYNK_WRITE(V3){
  servoPosition1 = param.asInt();
}
BLYNK_WRITE(V4){
  int pos1 = param.asInt(); // Get value from slider 
  servo2.write(pos1); // Set servo 1 position
}

// Check these values using the IF condition
void smartcar() {
  if (y > 70) {
    carForward();
    Serial.println("carForward");
  } else if (y < 30) {
    carBackward();
    Serial.println("carBackward");
  } else if (x < 30) {
    carLeft();
    // Add servo logic for turning left here if needed
    Serial.println("carLeft");
  } else if (x > 70) {
    carRight();
    // Add servo logic for turning right here if needed
    Serial.println("carRight");
  } else if (x < 70 && x > 30 && y < 70 && y > 30) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();// Run the blynk function
  smartcar();// Call the main function
    if(servoPosition1==1)
  {
  for(int i=0;i<=180;i=i+180)
  {
    servo1.write(i);
    delay(150);
  }
  for(int i=180;i>=0;i=i-180)
  {
    servo1.write(i);
    delay(150);
  }
  }
}

void carForward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carBackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carLeft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carRight() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}