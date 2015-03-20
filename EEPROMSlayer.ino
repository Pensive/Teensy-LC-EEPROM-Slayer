#include <EEPROM.h> // save settings to the eeprom

const byte EEPROM_Bytes = 128;
bool hasFailed;
int32_t failCount;
int32_t iteration;

int32_t lastChecksum;

void setup() {
  Serial.begin(9600);
  hasFailed = false;
  failCount =0;
  iteration =0;
  delay(3000); //give the serial monitor time to catch up
}

void blankEEPROM(){ //set EEPROM to all 0's
for (uint8_t i=0; i<EEPROM_Bytes; i++) {
   EEPROM.write(i,0);
  }  
}

void randomEEPROM(){
  lastChecksum=0;
  for (uint8_t i=0; i<EEPROM_Bytes; i++) {
    uint8_t randnum;
    randnum = byte(random(255));
   EEPROM.write(i,randnum);
   lastChecksum += randnum;
  }  
}

void fillEEPROM(){
  lastChecksum = 0;
  for (uint8_t i=0; i<EEPROM_Bytes; i++) {
   EEPROM.write(i,255);
   lastChecksum += 255;
  }  
}

int32_t readEEPROMChecksum(){
  int32_t EEPROMresult=0;
  for (uint8_t i=0; i<EEPROM_Bytes; i++) {
    EEPROMresult += EEPROM.read(i);
}
return EEPROMresult;
}

void loopTest(){
  iteration++;
  Serial.print("Test : ");
  Serial.print(iteration);
  Serial.print(" - Blank:");
  
  int32_t x = 0;
  blankEEPROM();
  x = readEEPROMChecksum();
  if (x != 0) {hasFailed = true; failCount++; Serial.print("FAIL, Random: ");}
  else
  {Serial.print("PASS, Random: ");}
  
  randomEEPROM();
   x = readEEPROMChecksum(); 
   if (x != lastChecksum) {hasFailed = true; failCount++; Serial.print("FAIL, Fill: ");}
  else
  {Serial.print("PASS, Fill: ");}
  
  fillEEPROM();
   x = readEEPROMChecksum(); 
   if (x != lastChecksum) {hasFailed = true; failCount++; Serial.print("FAIL. *** ");}
  else
  {Serial.print("PASS. *** ");}
  
  if (hasFailed) { Serial.print(" !!!! TOTAL FAILS:"); Serial.println(failCount); }
  else { Serial.println(" PERFECT."); }  
}

void loop() {
  
  loopTest();
  delay(1000);
  
}
