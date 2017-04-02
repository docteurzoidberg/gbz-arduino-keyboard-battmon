/* 
GameboyZero Keyboard + RGBLed&Serial Battery monitor for ATMEGA32u4/Leonardo. author: DrZoid<drzoid-gbz@tppt.eu> 
*/

#define KEYBOARD        //COMMENT IF NOT USING KEYBOARD
#define SERIAL          //COMMENT IF NOT USING SERIAL
#define BATTMON         //COMMENT IF NOT USING BATTMON
#define WS2812BLED      //COMMENT IF NOT USING WS2812b led

#ifdef KEYBOARD 
  #include <Keyboard.h>
#endif

void setup()
{
  #ifdef KEYBOARD
    keyboardSetup();
  #endif

  #ifdef BATTMON
    battmonSetup();
  #endif

  #ifdef WS2812BLED
    ledSetup();
  #endif
  
  #ifdef SERIAL
   serialSetup();
  #endif
  
  #ifdef KEYBOARD
    Keyboard.begin();
  #endif 
}

void loop()
{  
  #ifdef KEYBOARD
    keyboardLoop();
  #endif

  #ifdef BATTMON
    battmonLoop();
  #endif

  #ifdef WS2812BLED 
    ledLoop();
  #endif 

  #ifdef SERIAL  
    serialLoop();
  #endif
}

