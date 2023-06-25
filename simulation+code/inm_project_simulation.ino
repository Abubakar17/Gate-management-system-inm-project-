#include <SPI.h> //header file for serial communication
#include <Servo.h> //header file for servo motor
#include <SoftwareSerial.h> //header file for bluetooth module

#define BUZZER 2 //buzzer pin

String ID1 = "19C8D5BB";  // ID for a Day Scholar's card
String ID2 = "23F4E511"; // ID for a Hostellite's card
String tagID = ""; 

String name1 = "Hassan";
String status1 = "Dayscholar";
String cms1 = "337668";
bool set_flag1 = false;
String name2 = "Maheen";
String status2 = "Hostellite";
String cms2 = "334334";

int input;
int device = A1;
int green = 7; 
int red = 6; 


void setup() 
{
  // Initiating
  SPI.begin(); // SPI bus
  Serial.begin(9600); //baud rate for serial communication
  pinMode(device, INPUT);
  Serial.println("Initializing... Scan your card");
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

int id;
int id1;
int id2;

      
void loop()
{
  //Wait until new tag is available
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(BUZZER, LOW);
  
  if (Serial.available() > 0) {
  tagID = Serial.readString(); 
  
  id= tagID.toInt();
  id1 = ID1.toInt();
  id2 = ID2.toInt();

  
  if (id == id1) 
  {
    Serial.print(name1);
    Serial.print(",");
    Serial.print(status1);
    Serial.print(",");
    Serial.println(cms1);
    digitalWrite(BUZZER, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    delay(5000);
    Serial.println("SCAN YOUR CARD!");
  }

  
  else if (id == id2) 
  {
    Serial.print(name2);
    Serial.print(",");
    Serial.print(status2);
    Serial.print(",");
    Serial.println(cms2);
    digitalWrite(BUZZER, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    delay(5000);
    Serial.println("SCAN YOUR CARD!");
  }

  else 
  {
    Serial.println("Card Not Registered");
    Serial.println("SCAN YOUR CARD!");
  }
}
}
