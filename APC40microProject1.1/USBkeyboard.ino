// todo try to implement button hold function, try to use only desired values, or create some smart multi key calculation stuff.

byte keyBoard (byte key)
{
  switch (key) {
    case 16:
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.release(KEY_DOWN_ARROW); 
      Keyboard.release(KEY_RIGHT_SHIFT);
      break;
    case 8:
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_UP_ARROW);
      Keyboard.release(KEY_RIGHT_SHIFT);
      break;
    case 4:
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
      Keyboard.release(KEY_RIGHT_SHIFT);
      break;
    case 2:
      Keyboard.press(KEY_RIGHT_SHIFT);      
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.release(KEY_LEFT_ARROW);
      Keyboard.release(KEY_RIGHT_SHIFT);
      break;
    case 1:
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }

  //Keyboard.releaseAll();
return 0;
}



