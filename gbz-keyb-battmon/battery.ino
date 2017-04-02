#ifdef BATTMON

  #define READINGS_COUNT 100
  #define BAT_PIN A0
  #define CHARGE_PIN A1
  
  #define VREF 4.6
  #define BAT_EMPTY_VOLTS 3.0
  #define BAT_FULL_VOLTS 4.2
 
  

  //Battery infos
  const float battEmpty = (1023.0/VREF)*BAT_EMPTY_VOLTS;       //empty battery voltage = 3.0v
  const float battFull = (1023.0/VREF)*BAT_FULL_VOLTS;         //full battery voltage = 4.2v
  bool isCharging = false;
  bool isFull = false;  
  int batt = 0;
  float battVolts = 0.0;
  int battPercent = 0;  
 
  //Analog input smoothing
  unsigned short int readings[READINGS_COUNT];                  // the readings from the analog input  
  int readIndex = 0;                                            // the index of the current reading
  long total = 0;                                               // the running total
  int average = 0;                                              // the average
  bool buffFull = false;                                        
  
  int battmonLastPin = BAT_PIN;
  unsigned long battmonLastMillis = 0;

  
  

  void battmonSetup() {
    
    //Input mode pins
    pinMode(BAT_PIN, INPUT);
    pinMode(CHARGE_PIN, INPUT);

    //Empty memory
    for (int thisReading = 0; thisReading < READINGS_COUNT; thisReading++) {
      readings[thisReading] = 0;
    }
    
  }

  void battmonLoop() {

    int value = analogRead(battmonLastPin);
    delay(2);
    
    if(battmonLastPin==BAT_PIN) {

        total = total - readings[readIndex];
        readings[readIndex] = value;

        total = total + readings[readIndex];
        readIndex = readIndex + 1;
        
        if (readIndex >= READINGS_COUNT) {
            readIndex = 0;
            buffFull = true;
        }

        if(!buffFull) {
            average = total / readIndex;
        } else {
            average = total / READINGS_COUNT;
        }
    } 

    if(battmonLastPin==CHARGE_PIN) {
        isCharging = (value>500);
    }

    battmonLastPin = (battmonLastPin==BAT_PIN) ? CHARGE_PIN : BAT_PIN;

    //Sort si delai < 1 seconde depuis derriere execution
    if((millis()-battmonLastMillis) < 1000) {
        return;
    }
    
    batt = average;    
    battVolts =  batt * (vref / 1023.0);
    battPercent = map(average, battEmpty, battFull, 0, 100);
    battmonLastMillis = millis();
  }
  
#endif

