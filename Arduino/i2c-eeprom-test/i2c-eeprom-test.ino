// tester i2c  via serial
// the metal
// 3 bytes: cmd, hibyte, lobyte

#include <Wire.h>
#include <EEPROM.h>

byte x[3];
int cmd[8];
int flagg;
int z, y;

int hoi_pos=4000;
int mid_pos=3000;
int lav_pos=1000;
int servo;
unsigned long tid, vent;
unsigned long hoi_tid, mid_tid, mid_range, lav_tid, lav_range;
unsigned long hoi, mid, lav;
unsigned long mid_base, lav_base;

int dir, av, pause;
unsigned long on_base, off_base, on_range, off_range; //motor
unsigned long motor_tid, motor_nytid;

void setup() {
  Serial.begin(115200);
  Wire.begin(4);
  Wire.onReceive(receiveEvent); 
  for (int n=0; n<8; n++) {
    cmd[n]=readIntFromEEPROM(n*2);
    }
  servo=mid_pos;  
  hoi=7000;  
}

void loop() {
  tid=millis();
  mid_base=cmd[0]*1000UL;
  mid_range=cmd[1]*1000UL;
  lav_base=cmd[2]*1000UL;
  lav_range=cmd[3]*1000UL;
  on_base=cmd[4]*1000UL;
  on_range=cmd[5]*1000UL;
  off_base=cmd[6]*1000UL;
  off_range=cmd[7]*1000UL;
  
  if(tid-lav_tid>lav && servo==lav_pos) {
    servo=hoi_pos;
    hoi_tid=tid;
    }

  if(tid-hoi_tid>hoi && servo==hoi_pos) {
    servo=mid_pos;
    mid_tid=tid;
    mid = mid_base+random(mid_range);
      }

    if(tid-mid_tid>mid && servo==mid_pos) {
      servo=lav_pos;
      lav_tid=tid;
      lav=lav_base+random(lav_range);
      }

    if (tid-motor_tid>motor_nytid) {
      motor_tid=tid;
      if (pause==false) {
      motor_nytid=off_base+random(off_range);
      pause=true;
      }
    else {
      motor_nytid=on_base+random(on_range);
      pause=false;
      }  
    }  

  
    Serial.print(((x[0]&127)>>3));
    Serial.print(" ");

    for (int n=0; n<8; n++) {
    Serial.print(cmd[n]);
    Serial.print(" ");
    }
    Serial.print(tid-mid_tid);
    Serial.print(" ");
    Serial.print(mid);
    Serial.print("   ");
    Serial.print(tid-lav_tid);
    Serial.print(" ");
    Serial.print(lav);
    Serial.print("   ");
    Serial.print(tid-hoi_tid);
    Serial.print(" ");
    Serial.print(hoi);
    Serial.print(" ");
    Serial.print(tid-motor_tid);
    Serial.print(" ");
    Serial.print(motor_nytid);
    if (pause==true) Serial.println(" pause!");
    if (pause==false) Serial.println(" motor");
  
}

void writeIntoEEPROM(byte number[3]){ 
  EEPROM.write((number[0]&127)>>3, number[1]);
  EEPROM.write(((number[0]&127)>>3) + 1, number[2]);
}

int readIntFromEEPROM(int address){
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) | byte2;
}

void receiveEvent(int antall){
  for (int n = 0; n <= (antall-1); n++) {x[n] = Wire.read();}
  cmd[((x[0]&127)>>3)/2]=(x[1]<<8)|x[2]; 
  if (x[0]&128) writeIntoEEPROM(x);
  }  
