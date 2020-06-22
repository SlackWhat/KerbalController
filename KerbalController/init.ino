// Initialisation of the controls, set all pin modes
void controlsInit() {
  pinMode(pTHROTTLE, INPUT);
  pinMode(pTX, INPUT);
  pinMode(pTY, INPUT);
  pinMode(pTZ, INPUT);
  pinMode(pRX, INPUT);
  pinMode(pRY, INPUT);
  pinMode(pRZ, INPUT);
  pinMode(pPOWER, INPUT_PULLUP);
  pinMode(pTB, INPUT_PULLUP);
  pinMode(pRB, INPUT_PULLUP);
  pinMode(pMODE, INPUT_PULLUP);
  pinMode(pLCDx, INPUT_PULLUP);
  pinMode(pLCDy, INPUT_PULLUP);
  pinMode(pLCDz, INPUT_PULLUP);
  pinMode(pSAS, INPUT_PULLUP);
  pinMode(pRCS, INPUT_PULLUP);
  pinMode(pABORT, INPUT);
  pinMode(pARM, INPUT);
  pinMode(pSTAGE, INPUT_PULLUP);
  pinMode(pSTAGELED, OUTPUT);
  pinMode(pLIGHTS, INPUT_PULLUP);
  pinMode(pLIGHTSLED, OUTPUT);
  pinMode(pLADDER, INPUT_PULLUP);
  pinMode(pLADDERLED, OUTPUT);
  pinMode(pSOLAR, INPUT_PULLUP);
  pinMode(pSOLARLED, OUTPUT);
  pinMode(pCHUTES, INPUT_PULLUP);
  pinMode(pCHUTESLED, OUTPUT);
  pinMode(pGEARS, INPUT_PULLUP);
  pinMode(pGEARSLED, OUTPUT);
  pinMode(pBRAKES, INPUT_PULLUP);
  pinMode(pBRAKESLED, OUTPUT);
  pinMode(pACTION1, INPUT_PULLUP);
  pinMode(pACTION1LED, OUTPUT);
  pinMode(pACTION2, INPUT_PULLUP);
  pinMode(pACTION2LED, OUTPUT);
  pinMode(pACTION3, INPUT_PULLUP);
  pinMode(pACTION3LED, OUTPUT);
  pinMode(pACTION4, INPUT_PULLUP);
  pinMode(pACTION4LED, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

// Blink every LED once to test
void testLEDS(int testdelay) {
  digitalWrite(pSTAGELED,HIGH);
  delay(testdelay);
  digitalWrite(pSTAGELED,LOW);
  digitalWrite(pLIGHTSLED,HIGH);
  delay(testdelay);
  digitalWrite(pLIGHTSLED,LOW);
  digitalWrite(pLADDERLED,HIGH);
  delay(testdelay);
  digitalWrite(pLADDERLED,LOW);
  digitalWrite(pSOLARLED,HIGH);
  delay(testdelay);
  digitalWrite(pSOLARLED,LOW);
  digitalWrite(pCHUTESLED,HIGH);
  delay(testdelay);
  digitalWrite(pCHUTESLED,LOW);
  digitalWrite(pGEARSLED,HIGH);
  delay(testdelay);
  digitalWrite(pGEARSLED,LOW);
  digitalWrite(pBRAKESLED,HIGH);
  delay(testdelay);
  digitalWrite(pBRAKESLED,LOW);
  digitalWrite(pACTION1LED,HIGH);
  delay(testdelay);
  digitalWrite(pACTION1LED,LOW);
  digitalWrite(pACTION2LED,HIGH);
  delay(testdelay);
  digitalWrite(pACTION2LED,LOW);
  digitalWrite(pACTION3LED,HIGH);
  delay(testdelay);
  digitalWrite(pACTION3LED,LOW);
  digitalWrite(pACTION4LED,HIGH);
  delay(testdelay);
  digitalWrite(pACTION4LED,LOW);
  
  // Prepare the shift register
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);

  inputBytes[0] = B11111111;
  inputBytes[1] = B11111111;
  inputBytes[2] = B11111111;
  inputBytes[3] = B11111111;
  inputBytes[4] = B11111111;
  inputBytes[5] = B11111111;
  inputBytes[6] = B11111111;
  
  // Loop through the input bytes
  for (int j=0; j<=6; j++) {
    byte inputByte = inputBytes[j];
    Serial.println(inputByte);
    shiftOut(dataPin, clockPin, MSBFIRST, inputByte);
  }
  
  // Latch the values in when done shifting
  digitalWrite(latchPin, HIGH); 
  
  delay(testdelay);
  
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

// Welcome message on the LCD
void welcomeMessage() {
  randomNumber = random(6);

  if (randomNumber == 4 || !digitalRead(pSAS)) {
    writeLCD("We can always");
    jumpToLineTwo();
    writeLCD("  plan a rescue.");
  }
  else if (randomNumber == 3 || !digitalRead(pRCS)) {
    writeLCD("If in doubt, add");
    jumpToLineTwo();
    writeLCD("  more boosters.");
  }
  else if (randomNumber == 5 || !digitalRead(pLCDx) || !digitalRead(pLCDy) || !digitalRead(pLCDz)) {
    writeLCD("May the Kraken");
    jumpToLineTwo();
    writeLCD("not be in ur way");
  }
  else {
    writeLCD(" KSP Controller");
    jumpToLineTwo();
    writeLCD("#   Welcome!   #");
  }
}
