#ifdef WS2812BLED

  #define LED_COUNT 1
  #define LED_PIN 9
  
  #include <PololuLedStrip.h>
  
  rgb_color colors[LED_COUNT];
  PololuLedStrip<LED_PIN> ledStrip;
  
  unsigned long ledLastMillis = 0;
 
  void ledSet(int r, int g, int b) {
      rgb_color color;
      color.red = r;
      color.green = g;
      color.blue = b;
      colors[0]=color;  
      ledStrip.write(colors, LED_COUNT);
  }
  
  void ledSetup() {
     pinMode(LED_PIN, OUTPUT);
     
     //Start led with dim white
     ledSet(6,6,6);
  }
  
  void ledLoop() {
    
    if((millis() - ledLastMillis)<1000) 
      return;
    
    if(battPercent<110 && battPercent>75) 
    {
      //Green between 75 and 110%
      ledSet(0,12,0);
    } 
    else if(battPercent>50) 
    {
      //Lighter green between 50 and 75%
      ledSet(6,12,0);
    } 
    else if(battPercent>25) 
    {
      //Yellow between 25 and 50%
      ledSet(12,12,0);
    } 
    else if(battPercent>10) 
    {
      //Orange between 10 and 20%
      ledSet(12,6,0);
    } 
    else if(battPercent>=0) 
    {
      //Red < 10%
      ledSet(12,0,0);
    } 
    else 
    {
      //Blue => check code / hardware => bad voltage calculation
      ledSet(0,0,12);
    }
     
    ledLastMillis = millis();
 }
#endif
