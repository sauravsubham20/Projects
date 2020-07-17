#include <LiquidCrystal.h>
#include <OneWire.h>
#include <TinyGPS.h>
#define temp A6
#define obj 26
#define relay 31
#define key 30
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(15,14,13,12, 11, 4);
TinyGPS gps;
  char la[20]="22.560068";
  char lo[20]="72.919731";
volatile int stabpm=0;
unsigned long time10,time20;
unsigned long rateTime,timeR1,timeR2;
unsigned bpmRate;
float celsius, fahrenheit;
int bpmCount=0;
int averate;
int sta=0;
OneWire  ds(2);  // on pin 10 (a 4.7K resistor is necessary)
void bpm(){
  if(stabpm==0){
      time10=millis();
      stabpm=1;
  }
  else if(stabpm==1){
      time20=millis();
      stabpm=2;
  }
  
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(obj,INPUT);
  pinMode(key,INPUT);
  pinMode(relay,OUTPUT);
  // Print a message to the LCD.
  lcd.print("Patient Monitor");
  lcd.setCursor(0,1);
  lcd.print("    System     ");
  delay(1000);
  attachInterrupt(0, bpm, RISING);
  lcd.clear();
  Serial.begin(9600);
  delay(10000);
}

void loop() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  if(digitalRead(key)==HIGH){
     sta=0; 
  }
  if(sta==0){
    digitalWrite(relay,LOW);
  }
  else{
     digitalWrite(relay,HIGH); 
    
  }
  
  //////////////////////////////////////////// GPS DATA
  while (Serial.available()){
      bool newData = false;
      char c = Serial.read();
      if (gps.encode(c)){ // Did a new valid sentence come in?
        newData = true;
      }
      if (newData){
              lcd.clear();
              String gpslocation = "";
              float flat, flon;
              unsigned long age;
              gps.f_get_position(&flat, &flon, &age);
              dtostrf(flat, 8, 6, la);
              dtostrf(flon, 8, 6, lo);
              lcd.setCursor(0,0);
              lcd.print("LAT:");lcd.print(la);lcd.print("    ");
              lcd.setCursor(0,1);
              lcd.print("LON:");
              lcd.print(lo);lcd.print("    ");
              delay(5000);
      }
    }
  ///////////////////////////////////////////
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  
   if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }
  ds.reset();ds.select(addr);ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  delay(1000);     // maybe 750ms is enough, maybe not
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad
  for (int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  if(fahrenheit>98){
    if(sta==0){
       sta=1;
       sms(); 
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////  DS18B20
     if(stabpm==2){
      rateTime = time20 - time10;
      bpmRate = (60000/rateTime);
      stabpm=0;
      if((bpmRate>200)||(bpmRate<40)){
         bpmRate=0; 
         bpmCount=0;
      }
      else{
        
         bpmCount++;
         averate=averate+bpmRate;
         if(bpmCount==2){
           bpmCount=0;
           bpmRate=averate/2;
           lcd.setCursor(10,0);
           lcd.print("H:");lcd.print(bpmRate);lcd.print("   ");
           if((bpmRate>0)&&((bpmRate<50)||(bpmRate>170))){
            if(sta==0){
               sta=1;
             sms(); 
              }         
           }
           averate=0;
           bpmRate=0;
           
         }
        
      }
    }
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(fahrenheit);
  lcd.print("F  ");
  
if((millis()-time20)>3000){
  bpmRate=0;
  lcd.setCursor(10,0);
  lcd.print("H:");lcd.print(bpmRate);lcd.print("   ");
 }
  lcd.setCursor(0, 1);
  if(digitalRead(obj)==HIGH){
    lcd.print("Patient:Present");
  }
  else{
    lcd.print("Patient:Absent ");
    if(sta==0){
       sta=1;
       sms(); 
    }
  }
  //delay(1000);
}

void sms(){
        Serial.write("AT\r\n");
         Serial.write("AT\r\n");
          Serial.write("AT\r\n");
	delay(100);
	Serial.write("AT+CMGF=1\r\n");
	delay(100);
	Serial.write("AT+CMGS=\"9624252543\" \r\n");   //phone number for getting sms
        delay(100);
        Serial.print("Temperature:");Serial.println(fahrenheit);
        Serial.print("Heart Beat Rate:");Serial.println(bpmRate);
        if(digitalRead(obj)==HIGH){
              Serial.println("Patient : Present ");
        }
        else{
              Serial.println("Patient : Absent ");
        }

        Serial.print("LATITUDE:");Serial.println(la);
        Serial.print("LONGITUDE:");Serial.println(lo);
      	Serial.write("\r\n");
        delay(100); 
        Serial.write("\x1A \n");
        delay(100); 
        //rd='0';
        lcd.setCursor(0,1);
        lcd.print("SMS Sended...   "); 
        delay(3000);
}