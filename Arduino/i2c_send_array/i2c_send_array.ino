// The Metal
// mottar data serial
// sender i2c

#include <Wire.h>
byte x[5];

  
void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  
  if(Serial.available()) {
    Serial.readBytes(x,3);
    if (x[0]&7) i2c(x);
   //  Serial.write(x,4);
    
 
  }
}

void i2c(byte n[4]) {
  Wire.beginTransmission(x[0]&7);
  for (int p=0; p<3; p++) Wire.write(n[p]);
  Wire.endTransmission();
  
  
  }
