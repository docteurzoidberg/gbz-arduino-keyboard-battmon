#ifdef SERIAL

  unsigned long serialLastMillis = 0;
  
  void serialSetup() {
    Serial.begin(9600);
  }

  void serialLoop() {
  
    if((millis() - serialLastMillis)<1000)
      return;
    
    //TODO: packet forge
    Serial.write("!PKT");       //header
    Serial.write('b');          //type=battery status
    Serial.write(0x06);         //len
    Serial.write(battPercent);  //batt percent
    Serial.write(led1);         //batt charging
    Serial.write((byte)0);      //batt voltage 1/4
    Serial.write((byte)0);      //batt voltage 2/4
    Serial.write((byte)0);      //batt voltage 3/4
    Serial.write((byte)0);      //batt voltage 4/4
    Serial.write('\n');         //END
  
    serialLastMillis = millis();
  }

#endif
