
void muxRead() {

muxNr = PINB >> 5; // Read on which position is mux 
// besure to implement that it reads once, similar as debounce for keys, read repeatedly only if muxNr changes

if (lastMuxNr != muxNr)
{

  muxBank[muxNr+8] = analogRead(A0);
  muxBank[muxNr] = analogRead(A1);
  lastMuxNr = muxNr;
  //Serial.println(muxNr);

}
else;

}

float ReadPotRad (int x, int y, int precisioun) // int x and int y are the raw analog readings of doublepot, precision can by any size around 1608 is native. 350 could srand for degrees.
{
  float rad = atan2(x-511, y-511) * precision / 3.14159265359  ; // calculation of pot position in radiants x precision.
  return rad;
}

void potFromPotSetup() // this was as inittialization of variables from the reading int the setup but since in this case reading is happening after setup, it should be ran once and from variables stored in muxBank. 
{
    rad[0] = ReadPotRad (analogRead(A2), analogRead(A3), precision); 
    rad[1] = ReadPotRad (analogRead(A0), analogRead(A1), precision);

  for(int i=0; i<sizeof( lastrad ) / sizeof( float ); i++) lastrad[i] = rad[i];
}

void potFromPotLoop() // from loop 
{
  rad[0] = ReadPotRad (analogRead(A2), analogRead(A3), precision); 
  rad[1] = ReadPotRad (analogRead(A0), analogRead(A1), precision);

    
    int i = rad[0]/50+5;
    potBank[i] += potChange (lastrad[1], rad[1], precision);
  
    // print the results to the serial monitor:
    Serial.print(i);
    Serial.print("sensor = ");
    Serial.print(potBank[i]);
    
    Serial.println(" , ");
 
  
  for(int i=0; i<sizeof( lastrad ) / sizeof( float ); i++) lastrad[i] = rad[i];
}


float potChange (float vOLD, float vNEW, int vPRECISION) // tab was called relative pot mapping // dual pot maping. ino from electronics folder in Controller Q is the originalle 
{
  float output = 0;
  
  if (vOLD > 0 && vNEW < 0) 
  {
    output = -2*vPRECISION+vOLD-vNEW;

    return output;
  }
  
  if (vOLD < 0 && vNEW > 0) 
  {
    output = 2*vPRECISION+vOLD-vNEW;

    return output;
  }
  else
    output = vNEW - vOLD;

    return output;
  
}

void rotaryPot() // function for 360 deg rotary as potentiometer
{
  
}

void rotaryEncoder() // function to use rotary as encoder
{
  
}

