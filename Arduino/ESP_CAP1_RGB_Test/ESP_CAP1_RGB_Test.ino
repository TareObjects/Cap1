


const int kRed   = 14;
const int kGreen = 15;
const int kBlue  = 12;


#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include "STTS751.h"

STTS751 stts751;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start");

  //  analogWriteRange(64);
  
  Serial.println("Init");
  pinMode(kRed,   OUTPUT);
  pinMode(kGreen, OUTPUT);
  pinMode(kBlue,  OUTPUT);
  
  Serial.println("Go");

  Wire.begin();
  
  stts751.setup(0x38);  // 20kΩ
  
  }

const int kOn = 255;
const int kOff =  0;

const int kMaxRed   = 510;
const int kMaxGreen = 620;
const int kMaxBlue  = 730;

float r = 0;
float g = 0;
float b = 0;

int prevSec = 0;


void loop() {
  int rw = (float)kOn * sin(r / (float)kMaxRed * 6.28) + (float)kOn;
  analogWrite(kRed, rw);
  //Serial.println(rw);
  r++;

  int gw = (float)kOn * sin(g / (float)kMaxGreen * 6.28) + (float)kOn;
  analogWrite(kGreen, gw);
  g++;
  
  int bw = (float)kOn * sin(b / (float)kMaxBlue * 6.28) + (float)kOn;
  analogWrite(kBlue, bw);
  b++;

  if (prevSec != second()) {
      Serial.print("temperature = ");
      float temperature = stts751.readTemperature();
      Serial.println(temperature);

      prevSec = second();
  }
  delay(5);
}
