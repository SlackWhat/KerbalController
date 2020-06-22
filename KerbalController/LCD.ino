// Clear the LCD by writing all spaces
void clearLCD() {
  jumpToStart();
  mySerial.write("                ");
  mySerial.write("                ");
  jumpToStart();
}

// Jump to the start of the first line on the LCD
void jumpToStart() {
  mySerial.write(254);
  mySerial.write(128);
}

// Jump to the start of the second line on the LCD
void jumpToLineTwo() {
  
  mySerial.write(254);
  mySerial.write(192);
}

// Write text to the LCD
void writeLCD(char myText[]) {
  mySerial.write(myText);
}

// Change the brightness of the LCD
void setLCDlight(byte brightness) {
  mySerial.write(0x7c);         // Prepare the backlight command
  mySerial.write(brightness);   // Send the brightness value
}
