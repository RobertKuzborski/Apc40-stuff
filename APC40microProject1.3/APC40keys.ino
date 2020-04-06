// Todo: try to solve this serial sending X thing, because if port is not requested from pc side then it is not nais. Open serial println and see what helps there
void keyRead()
{
  //Serial.println(""); //necessary to keep this serial print because otherwise it doesnt work !!!!! ASwell if serial not intiliazed from pc works really bad what bout this serial here??
  //keyID = PIND; maybe it causes delay for precisely one clock???
  delayMicroseconds(15); //yeah that serial was causing some kind of delay ...
  keyID = PIND; // read port D
  keyID &= ~(1 << 5); // since pin5 is high due to present TXLED owerwrite it with zero. as well it simply bypassess that pin and next pin has its value if pressed

  looptimer = 0;
  //keyState = HIGH; // remember that key is pressed

  //keyDebounce(); //Because interrupt might happen anytime it fucks up with code by changing variable during the debounce happening.

  //keyDebounce2();

  //if last id = current id dont send it.
  //keyBoard (keyID);
  //delay(10);

}

void keyRuntimeAndDebounce()
{
  if (keyID == lastkeyID && keyID == 0)
  {
    lastkeyID = keyID; // if all zero set zero
  }
  else if ( lastkeyID == keyID && lastkeyID != 0)
  {
    lastkeyID = keyID; //keep keyID same as they were
  }
  else if (lastkeyID != keyID && keyID != 0)
  {
    //MserialDebugKeys(); //////

    keyBoard (keyID); //Send key
    lastkeyID = keyID; // update keyID since these changed
  }
  else if (lastkeyID != keyID && keyID == 0)
  {
    lastkeyID = 0;
  }
  else if ( lastkeyID != keyID && lastkeyID == 0)
  {
    //serialDebugKeys(); /////

    keyBoard (keyID); //Send key
    lastkeyID = keyID;
  }
}

void serialDebugKeys()
{
  Serial.print("YES!! : ");
  Serial.println(keyID);
  Serial.println(looptimer);
}


