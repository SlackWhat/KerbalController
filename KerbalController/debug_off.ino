void debug_mode() {

  /* -------------------------------------------------
   * Debug mode does not communicate with KSPSerialIO,
   * but simply displays the button states on the LCD.
   * Select analog input using LCDx/y/z.
   * Xyz = Throttle.
   * xYz = Translation.
   * xyZ = Rotation.
   * ZYZ = Fuel gauges.
   * ------------------------------------------------- */

  // Previous state tracking only used in debug
  bool stage_prev = false;
  bool lights_prev = false;
  bool ladder_prev = false;
  bool solar_prev = false;
  bool gears_prev = false;
  bool brakes_prev = false;
  bool chutes_prev = false;
  bool action1_prev = false;
  bool action2_prev = false;
  bool action3_prev = false;
  bool action4_prev = false;
  
  // Qty number for fuel gauges testing
  int qty;

  // Clear the LCD 
  clearLCD();
    
  // Toggle switches
  if (!digitalRead(pSAS)) { writeLCD("S"); } else { writeLCD("s"); }
  if (!digitalRead(pRCS)) { writeLCD("R"); } else { writeLCD("r"); }
  if (digitalRead(pABORT)) { writeLCD("A"); } else { writeLCD("a"); }   // Note: abort switch is active high
  if (digitalRead(pARM)) { writeLCD("A"); } else { writeLCD("a"); }     // Note: arm switch is active high
   
  // In debug mode, handle all buttons as toggle buttons
  if (!digitalRead(pSTAGE) && !stage_prev) { stage_on = !stage_on; stage_prev = true; delay(100); }
  if (digitalRead(pSTAGE) && stage_prev) { stage_prev = false; delay(100); }
  if (stage_on) { writeLCD("S"); } else { writeLCD("s"); }
  digitalWrite(pSTAGELED, stage_on);

  if (!digitalRead(pLIGHTS) && !lights_prev) { lights_on = !lights_on; lights_prev = true; delay(50); }
  if (digitalRead(pLIGHTS) && lights_prev) { lights_prev = false; delay(50); }
  if (lights_on) { writeLCD("L"); } else { writeLCD("l"); }
  digitalWrite(pLIGHTSLED, lights_on);
    
  if (!digitalRead(pLADDER) && !ladder_prev) { ladder_on = !ladder_on; ladder_prev = true; delay(100); }
  if (digitalRead(pLADDER) && ladder_prev) { ladder_prev = false; delay(100); delay(50); }
  if (ladder_on) { writeLCD("L"); } else { writeLCD("l"); }
  digitalWrite(pLADDERLED, ladder_on);
    
  if (!digitalRead(pSOLAR) && !solar_prev) { solar_on = !solar_on; solar_prev = true; delay(50); }
  if (digitalRead(pSOLAR) && solar_prev) { solar_prev = false; delay(50); }
  if (solar_on) { writeLCD("S"); } else { writeLCD("s"); }
  digitalWrite(pSOLARLED, solar_on);
  
  if (!digitalRead(pCHUTES) && !chutes_prev) { chutes_on = !chutes_on; chutes_prev = true; delay(50); }
  if (digitalRead(pCHUTES) && chutes_prev) { chutes_prev = false; delay(50); }
  if (chutes_on) { writeLCD("C"); } else { writeLCD("c"); }
  digitalWrite(pCHUTESLED, chutes_on);
    
  if (!digitalRead(pGEARS) && !gears_prev) { gears_on = !gears_on; gears_prev = true; delay(50); }
  if (digitalRead(pGEARS) && gears_prev) { gears_prev = false; delay(50); }
  if (gears_on) { writeLCD("G"); } else { writeLCD("g"); }
  digitalWrite(pGEARSLED, gears_on);
  
  if (!digitalRead(pBRAKES) && !brakes_prev) { brakes_on = !brakes_on; brakes_prev = true; delay(50); }
  if (digitalRead(pBRAKES) && brakes_prev) { brakes_prev = false; }
  if (brakes_on) { writeLCD("B"); } else { writeLCD("b"); }
  digitalWrite(pBRAKESLED, brakes_on);

  if (!digitalRead(pACTION1) && !action1_prev) { action1_on = !action1_on; action1_prev = true; delay(50); }
  if (digitalRead(pACTION1) && action1_prev) { action1_prev = false; delay(50); }
  if (action1_on) { writeLCD("A"); } else { writeLCD("a"); }
  digitalWrite(pACTION1LED, action1_on);
    
  if (!digitalRead(pACTION2) && !action2_prev) { action2_on = !action2_on; action2_prev = true; delay(50); }
  if (digitalRead(pACTION2) && action2_prev) { action2_prev = false; delay(50); }
  if (action2_on) { writeLCD("A"); } else { writeLCD("a"); }
  digitalWrite(pACTION2LED, action2_on);
    
  if (!digitalRead(pACTION3) && !action3_prev) { action3_on = !action3_on; action3_prev = true; delay(50); }
  if (digitalRead(pACTION3) && action3_prev) { action3_prev = false; delay(50); }
  if (action3_on) { writeLCD("A"); } else { writeLCD("a"); }
  digitalWrite(pACTION3LED, action3_on);
  
  if (!digitalRead(pACTION4) && !action4_prev) { action4_on = !action4_on; action4_prev = true; delay(50); }
  if (digitalRead(pACTION4) && action4_prev) { action4_prev = false; delay(50); }
  if (action4_on) { writeLCD("A"); } else { writeLCD("a"); }
  digitalWrite(pACTION4LED, action4_on);
    
  if (!digitalRead(pTB) && !tb_prev) {tb_on = !tb_on; tb_prev = true; }
  if (digitalRead(pTB) && tb_prev) {tb_prev = false; }
  if (tb_on) { writeLCD("T"); } else { writeLCD("t"); }
 
  if (!digitalRead(pRB) && !rb_prev) {rb_on = !rb_on; rb_prev = true; }
  if (digitalRead(pRB) && rb_prev) {rb_prev = false; }
  if (rb_on) { writeLCD("R"); } else { writeLCD("r"); }
  
  // Analog inputs
  // Throttle
  if (!digitalRead(pLCDx) && digitalRead(pLCDy) && digitalRead(pLCDz)) {
    throttle_value = analogRead(pTHROTTLE);
    char throttle_char[5];
    itoa(throttle_value, throttle_char, 10);
    writeLCD(throttle_char);
    writeLCD(" ");
  }

  // Translation joystick
  if (digitalRead(pLCDx) && !digitalRead(pLCDy) && digitalRead(pLCDz)) {
    tx_value = analogRead(pTX);
    char tx_char[5];
    itoa(tx_value, tx_char, 10);
    writeLCD(tx_char);
    writeLCD(" ");
    ty_value = analogRead(pTY);
    char ty_char[5];
    itoa(ty_value, ty_char, 10);
    writeLCD(ty_char);
    writeLCD(" ");
    tz_value = analogRead(pTZ);
    char tz_char[5];
    itoa(tz_value, tz_char, 10);
    writeLCD(tz_char);
    writeLCD(" ");
  }

  // Rotation joystick
  if (digitalRead(pLCDx) && digitalRead(pLCDy) && !digitalRead(pLCDz)) { 
    rx_value = analogRead(pRX);
    char rx_char[5];
    itoa(rx_value, rx_char, 10);
    writeLCD(rx_char);
    writeLCD(" ");    
    ry_value = analogRead(pRY);
    char ry_char[5];
    itoa(ry_value, ry_char, 10);
    writeLCD(ry_char);
    writeLCD(" ");
    rz_value = analogRead(pRZ);
    char rz_char[5];
    itoa(rz_value, rz_char, 10);
    writeLCD(rz_char);
  }

  // Fuel gauges qty test
  if (!digitalRead(pLCDx) && !digitalRead(pLCDy) && !digitalRead(pLCDz)) {
    clearLCD();
    writeLCD("FUEL QTY TEST");
    for (int percent=9; percent>=0; percent--) {
      jumpToLineTwo();
        
      if (percent == 0) { writeLCD("100%"); }
      if (percent == 1) { writeLCD("90%"); }
      if (percent == 2) { writeLCD("80%"); }
      if (percent == 3) { writeLCD("70%"); }
      if (percent == 4) { writeLCD("60%"); }
      if (percent == 5) { writeLCD("50%"); }
      if (percent == 6) { writeLCD("40%"); }
      if (percent == 7) { writeLCD("30%"); }
      if (percent == 8) { writeLCD("20%"); }
      if (percent == 9) { writeLCD("10%"); }
        
      qty = 0.1+pow(2,percent);
       
      inputBytes[0] = qty >> 6;
      inputBytes[1] = (qty << 2) | (qty >> 8);
      inputBytes[2] = qty;
      inputBytes[3] = qty >> 3;
      bitWrite(inputBytes[3], 0, bitRead(qty, 4)); // Fix the skipped 595 pin
      inputBytes[4] = (qty << 4) | (qty >> 6);
      inputBytes[5] = (qty << 2) | (qty >> 8);
      inputBytes[6] = qty;
       
      // Prepare the shift register
      digitalWrite(dataPin, LOW);
      digitalWrite(clockPin, LOW);
      digitalWrite(latchPin, LOW);
       
      // Loop through the input bytes
      for (int j=0; j<=6; j++) {
        byte inputByte = inputBytes[j];
        Serial.println(inputByte);
        shiftOut(dataPin, clockPin, MSBFIRST, inputByte);
      }
      
      // Latch the values in when done shifting
      digitalWrite(latchPin, HIGH); 
      delay(500);
    }
  }
  // End of debug mode
}

void shutControllerOff() {
  clearLCD();
  setLCDlight(128);      // Switch off LCD
  switchOffLEDS();       // Switch off LEDs

  // Looping until the power switch is back on
  while (digitalRead(pPOWER));

  // Restarting the controller
  setLCDlight(157);
  delay(500);
  welcomeMessage();
  delay(100);
  testLEDS(50);           // Blink every LED once to test (with a delay of 10 ms)
}

void switchOffLEDS() {
  digitalWrite(pSTAGELED,LOW);
  digitalWrite(pLIGHTSLED,LOW);
  digitalWrite(pLADDERLED,LOW);
  digitalWrite(pSOLARLED,LOW);
  digitalWrite(pCHUTESLED,LOW);
  digitalWrite(pGEARSLED,LOW);
  digitalWrite(pBRAKESLED,LOW);
  digitalWrite(pACTION1LED,LOW);
  digitalWrite(pACTION2LED,LOW);
  digitalWrite(pACTION3LED,LOW);
  digitalWrite(pACTION4LED,LOW);

  // Switching off the fuel gauges
  // Prepare the shift register
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);

  inputBytes[0] = B00000000;
  inputBytes[1] = B00000000;
  inputBytes[2] = B00000000;
  inputBytes[3] = B00000000;
  inputBytes[4] = B00000000;
  inputBytes[5] = B00000000;
  inputBytes[6] = B00000000;
  
  // Loop through the input bytes
  for (int j=0; j<=6; j++) {
    byte inputByte = inputBytes[j];
    Serial.println(inputByte);
    shiftOut(dataPin, clockPin, MSBFIRST, inputByte);
  }
  
  // Latch the values in when done shifting
  digitalWrite(latchPin, HIGH); 
}
