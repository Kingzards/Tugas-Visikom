#include <Adafruit_Fingerprint.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int fingerprintID = 0;
String IDname;


LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()  
{
  lcd.begin();
	lcd.backlight();
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  lcd.clear();
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  lcd.print("Adafruit finger detect test");
  delay(5);
  if (finger.verifyPassword()) {
    lcd.clear();
    Serial.println("Found fingerprint sensor!");
    lcd.setCursor(2, 0);
    lcd.print("Sensor Finger");
    lcd.setCursor(3, 1);
    lcd.print("Ditemukan!");
  } else {
    lcd.clear();
    Serial.println("Did not find fingerprint sensor :(");
    lcd.print("Did not find fingerprint sensor :(");    
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  // lcd.clear();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  // lcd.write(Serial.read());

}
void displayUserGreeting(String IDname){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello");
  lcd.setCursor(0,1);
  lcd.print(IDname); 

  delay(200);
  fingerprintID = 0; 
}

void loop()                     // run over and over again
{

  getFingerprintID();
  

}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      Serial.println("Image taken");
      lcd.print("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      Serial.println("Image converted");
      lcd.print("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    Serial.println("Found a print match!");
    lcd.print("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  lcd.clear();
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  // lcd.print(Serial.read()); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  lcd.print("Found ID #");
  lcd.print(finger.fingerID);
  fingerprintID = finger.fingerID;
  delay(100);            //don't ned to run this at full speed.
  if(fingerprintID == 1){
    lcd.clear();
    IDname = "Chici";
    lcd.setCursor(0,1);
    lcd.print(IDname);
    lcd.setCursor(0,0);
    lcd.print("2004873");            
  }  
  else if(fingerprintID == 2 || fingerprintID == 10){
    lcd.clear();
    IDname = "Taufik";  
    lcd.setCursor(0,1);
    lcd.print(IDname);
    lcd.setCursor(0,0);
    lcd.print("2003258");  
  } 
  else if(fingerprintID == 3){
    lcd.clear();
    IDname = "Naufal";  
    lcd.setCursor(0,1);
    lcd.print(IDname);
    lcd.setCursor(0,0);
    lcd.print("2002946");  
  } 
  delay(1000);  
  return finger.fingerID;
}

// // returns -1 if failed, otherwise returns ID #
// int getFingerprintIDez() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK)  return -1;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK)  return -1;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK)  return -1;
  
//   // found a match!
//   Serial.print("Found ID #"); Serial.print(finger.fingerID); 
//   Serial.print(" with confidence of "); Serial.println(finger.confidence);
  
  

// }
