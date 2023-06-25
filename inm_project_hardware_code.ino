#include <SPI.h> //header file for serial communication
#include <MFRC522.h> //header file for RFID Card reader
#include <Servo.h> //header file for servo motor
#include <SoftwareSerial.h> //header file for bluetooth module

#define RST_PIN 9 //reset pin
#define SS_PIN 10 //slave set pin
#define BUZZER 2 //buzzer pin

byte readCard[4];
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
bool set_flag2 = false;
Servo myServo; //defining servo motor name


SoftwareSerial bluetooth(10, 11); //RX, TX
int input;
int device = A1;
int green = 12; 
int red = 11; 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create instances


void setup() 
{
  // Initiating
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522
  Serial.begin(9600); //baud rate for serial communication
  pinMode(device, INPUT);
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;

}


void loop()
{
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  //Wait until new tag is available
  myServo.write(0);
  
  while (getID()) 
  {
    
    if (tagID == ID1) 
    {
      Serial.print(name1);
      Serial.print(",");
      Serial.print(status1);
      Serial.print(",");
      Serial.println(cms1);
      set_flag1 = true;
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
      myServo.write(90);

      delay(5000);
    }

    
    else if (tagID == ID2) 
    {
      Serial.print(name2);
      Serial.print(",");
      Serial.print(status2);
      Serial.print(",");
      Serial.println(cms2);
      set_flag2 = true;
      myServo.write(90);
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);

      delay(5000);
    }

    else 
    {
      Serial.print(",,");
      Serial.print("Card Not Registered");
    }
   }
}
