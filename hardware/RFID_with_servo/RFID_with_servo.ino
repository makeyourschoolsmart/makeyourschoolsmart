/*
 * http://geek.adachsoft.com
 * 
 * 
 * 
*/
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>


//#define LED_PIN A0
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

//#define SERVO_PIN 3
//Servo myservo;  // create servo object to control a servo
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("For more: http://geek.adachsoft.com");
  Serial.println("Arduino RFID lock");
  Serial.println("");

  myservo.attach(SERVO_PIN);
  myservo.write( 0 );


  pixels.begin();
  pixels.setPixelColor(0, 32, 32, 32);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0, 0, 0, 0);
  pixels.show();
}

void loop(){
  //Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent() ){
    return;
  }
  //Select one of the cards
  if ( !mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  
  String content= "";
  byte letter;
  for( byte i = 0; i < mfrc522.uid.size; i++ ){
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     if( i < mfrc522.uid.size-1 ) content+="-";
  }
  content.toUpperCase();
  Serial.println();
  Serial.println("UID tag :'" + content + "'");

  if( content == "77-39-50-39" ){
    Serial.println("Authorized access");
    myservo.write( 90 );

    pixels.setPixelColor(0, 0, 32, 0);
    pixels.show();
    
    delay(1000);
    myservo.write( 0 );

    pixels.setPixelColor(0, 0, 0, 0);
    pixels.show();
  }else{
    Serial.println("Access denied");
    pixels.setPixelColor(0, 32, 0, 0);
    pixels.show();
    delay(500);
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.show();
  }
  
  delay(1000);
} 
