#include <EEPROM.h>

void erase(void) {
  for (int i = 0 ; i < EEPROM.length() ; i++)
    EEPROM.write(i, 0);
}

void writeIntIntoEEPROM(int address, int number)
{ 
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
}

int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

int startTime;
int led_on;
int blink_time;
String buffer;
  
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  blink_time = readIntFromEEPROM(0); //1000;
  startTime = millis();
  led_on = 0;
}

// the loop function runs over and over again forever
void loop() {
  int currentMillis = millis();
  if ((currentMillis - startTime) >= blink_time) {
    if (led_on == 0) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      led_on = 1;   
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      led_on = 0;      
    }
    startTime = currentMillis;
  }
  if (Serial.available()) {
    char inByte = Serial.read();
    if (inByte == 's') {
      writeIntIntoEEPROM(0, blink_time);
    }
    else if (inByte != '\n') {
      buffer += inByte;
    }
    else {
      blink_time = buffer.toInt();
      buffer = "";
      Serial.println(blink_time);
    }
  }
}
