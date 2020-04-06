
#include "MIDIUSB.h"
#include "Keyboard.h"


const byte interruptPin = 7;

int looptimer = 0;
byte muxState = 0; // remember last state of multiplexer in order not to execute same reading multiple times
byte keyID = 0;
byte lastkeyID = 0;
bool keyState = 0; // key state from port read?
bool keyPressed = 0; //save keyboard button states for debounce
bool keyOn = 0;
bool sendKey = 0;
bool keyReadAllow = 0;

byte muxNr = 0;
byte lastMuxNr = 0;
//int muxBank0[8] = { 0,0,0,0,0,0,0,0 };
//int lastmuxBank0[8] = { 0,0,0,0,0,0,0,0 };
int muxBank[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int lastmuxBank[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

float potRad = 0;
int potBank = 0; //for pots after processed rads


int precision = 1024; //1657
float rad[2] = {0,0}; //variable for current rotary pot position
float lastrad[2] = {0,0}; //varialble for last rotary pot position
//float potBank[10] = {0,0,0,0,0,0,0,0,0,0}; // final value bank of rotary pots


void setup() {
  analogReference(EXTERNAL);
  //Serial.begin(115200); // for Monitoring and Debugging
  Keyboard.begin(); // USB Keyboard
  

  //pinMode(interruptPin, INPUT_PULLUP);  // Because by default it is high // no need
  DDRD = DDRD | B11000000; // sets port D two last pins to output in order to ignore reading of these - Reading keys
  DDRB = DDRB | B00011111; // sets port D two last pins to output in order to ignore reading of these - Reading Mux  pb 5,6,7
  attachInterrupt(digitalPinToInterrupt(interruptPin), keyRead, FALLING); //read which key is pressed and edit key mapping in USNkeyboard tab >>> function keyBoard
}

void loop() { //usbmidi capable to go > 500 fps insane!!! 
    if (looptimer > 2000)  // looptimer is implemented to replace milis. it is here to solve the debuncing of buttons (higher value for faster running program) (2000 standard)
  {
    looptimer = 0;
    keyID = 0;
  }
  looptimer ++; //read pots every second loop


  if ((looptimer %2) == 0) muxRead(); //read pots every second loop  < this makes mux reads accurate!!!

  if ((looptimer %2) != 0) // This saves some resources one loop is reading another loop is sending 
{
  receiveMIDI(); // receive midi in case midi output is enabled in software
  keyReadAllow = 1;
  for (byte i = 0; i < 10 ; i++) // send midi
  {
    if (lastmuxBank[i] != muxBank[i] && lastmuxBank[i] +1 != muxBank[i] && lastmuxBank[i] -1 != muxBank[i] ) //&& lastmuxBank[i] +2 != muxBank[i] && lastmuxBank[i] -2 != muxBank[i]) // do not send if value have changed only +- 1  = prevent sending all the time // 
    {
    //// New mapping method !!! WORKS FINE !!!
    pitchBend(i, (muxBank[i] << 4)+(muxBank[i] >> 6) );   // sends pitchbend, as well maps from 10 bit to 14 bit
    lastmuxBank[i] = muxBank[i]; //save last reading

    // keyboard send
    //keyRuntimeAndDebounce(); //test, clear it on cleanup


     
    }
  }
  //potRad = ReadPotRad(muxBank[9], muxBank[10], precision);//calculate rad position of pot
  keyReadAllow = 0;
  MidiUSB.flush();
}

        if(sendKey) 
      {
        keyRuntimeAndDebounce(); //original place, try put it in looptimer split
        sendKey = 0;
      }
 
  //keyPressed = LOW;
  //keyBoardTest ();
 //keyPressed = LOW;
  
  //Serial.println("Sending note on");
  //pitchBend(0, 16383);   // Channel 0, middle C, normal velocity
  //MidiUSB.flush();
  //delay(200);
  //Serial.println("Sending note off");
  //pitchBend(0, 0);  // Channel 0, middle C, normal velocity
  //MidiUSB.flush();
  //delay(500);


//keyState = LOW; // clean key state /release buttons
  
  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65

}

//try to implement kayboard, then join with multiplexer reader and sample 2 x8 - 8 faders + master encoder and optional stuff
//capture only these 2 groups, store in arrays, and in meanwhile do the computation of tangent and send data
//in version 2 implement receive port and implement leds for feedback
//in version 3 add 2 more midi cables and try full flex setup with other
