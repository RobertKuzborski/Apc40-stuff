
#include <Firmata.h>

int muxBank[6][8] = { 
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
};

byte muxNr = 0;
byte lastmuxNr = 0;
volatile bool binMux[3] = {0,0,0};



void setup()
{
 
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(2, checkMux, CHANGE);
}

void loop()
{

 //binMux[0] = digitalRead(2);
 //binMux[1] = digitalRead(3);
 binMux[2] = digitalRead(2);

  Serial.print(binMux[0]);
  Serial.print(binMux[1]);
  Serial.println(binMux[2]);
  
 //Firmata.sendAnalog(analogPin, analogRead(analogPin));
 // analogPin = analogPin + 1;
 // if (analogPin >= 64) analogPin = 0;
}

void checkMux () 
{
  muxNr = 0;
 //muxNr = digitalRead(3) << 0;
 //muxNr = digitalRead(4) << 1;
 //muxNr = digitalRead(5) << 2;
 binMux[0] = digitalRead(2);
 binMux[1] = digitalRead(3);
 //binMux[2] = digitalRead(4);
//lastmuxNr = muxNr;
//for (int i = 0; i <8; i++)
//muxBank [muxNr] [i] = analogRead (i);


 
}

