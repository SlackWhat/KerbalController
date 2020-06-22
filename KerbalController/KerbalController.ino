/*
 * Kerbal Space Program Controller
 * Arduino code
 * 
 * Modified by Morte-Couille (SlackWhat)
 * Original work from hugopeeters (https://github.com/hugopeeters)
 * And KSPSerialIO by zitronen (https://github.com/zitron-git/KSPSerialIO)
 * 
 */

#include <SoftwareSerial.h>
SoftwareSerial mySerial(15,14);   // Pin 14 connected to LCD, 15 unconnected

// Analog pins
const int pTHROTTLE = A0;   // Slide pot

// ----------------------
//        TO CHECK
// ----------------------

const int pTX = A1;         // Translation X-axis
const int pTY = A2;         // Translation Y-axis
const int pTZ = A3;         // Translation Z-axis

const int pRX = A4;         // Rotation X-axis
const int pRY = A5;         // Rotation Y-axis
const int pRZ = A6;         // Rotation Z-axis

/*
const int pTX = A4;         // Translation X-axis
const int pTY = A3;         // Translation Y-axis
const int pTZ = A1;         // Translation Z-axis

const int pRX = A2;         // Rotation X-axis
const int pRY = A5;         // Rotation Y-axis
const int pRZ = A6;         // Rotation Z-axis
*/

//toggle button states MODIFIED TO FALSE
bool tb_on = false;
bool rb_on = false;

// Previous button state
bool tb_prev = false;
bool rb_prev = false;

int navballMode;
int sasMode;

// ----------------------
//     TO CHECK END
// ----------------------

// Digital pins
const int pPOWER = 2;       // Power switch
const int pTB = 3;          // Translation joystick button
const int pRB = 4;          // Rotation joystick button
const int latchPin = 8;     // ST_CP - green wire
const int dataPin = 10;     // DS - yellow wire
const int clockPin = 11;    // SH_CP - blue wire
const int pMODE = 22;       // Mode switch (used for debug mode)
const int pLCDx = 29;       // Toggle switch x (used for LCD display modes)
const int pLCDy = 24;       // Toggle switch y (used for LCD display modes)
const int pLCDz = 27;       // Toggle switch z (used for LCD display modes)
const int pSAS = 26;        // SAS switch
const int pRCS = 31;        // RCS switch
const int pABORT = 28;      // Abort switch (safety switch, active high)
const int pARM = 30;        // Arm switch (safety switch, active high)
const int pSTAGE = 32;      // Stage button
const int pSTAGELED = 33;   // Stage button LED
const int pLIGHTS = 34;     // Lights button
const int pLIGHTSLED = 35;  // Lights button LED
const int pLADDER = 36;     // Ladder button (action group 5)
const int pLADDERLED = 37;  // Ladder button LED
const int pSOLAR = 38;      // Solar button (action group 6)
const int pSOLARLED = 39;   // Solar button LED
const int pCHUTES = 40;     // Chutes button (action group 7)
const int pCHUTESLED = 41;  // Chutes button LED
const int pGEARS = 42;      // Gears button
const int pGEARSLED = 43;   // Gears button LED
const int pBRAKES = 44;     // Brakes button
const int pBRAKESLED = 45;  // Brakes button LED
const int pACTION1 = 46;    // Action Group 1 button
const int pACTION1LED = 47; // Action Group 1 button LED
const int pACTION2 = 48;    // Action Group 2 button
const int pACTION2LED = 51; // Action Group 2 button LED
const int pACTION3 = 50;    // Action Group 3 button
const int pACTION3LED = 49; // Action Group 3 button LED
const int pACTION4 = 52;    // Action Group 4 button
const int pACTION4LED = 53; // Action Group 4 button LED

// In-game state - Used to update button LEDs
bool lights_on = false;
bool ladder_on = false;
bool solar_on = false;
bool gears_on = false;
bool brakes_on = false;
bool chutes_on = false;
bool stage_on = false;
bool action1_on = false;
bool action2_on = false;
bool action3_on = false;
bool action4_on = false;

// Stage button LED state
bool stage_led_on = false;

// Input value variables
int throttle_value;
int tx_value;
int ty_value;
int tz_value;
int rx_value;
int ry_value;
int rz_value;

// Variables used for fuel gauges
byte inputBytes[7];
int vSF, vLF, vOX, vEL, vMP, SF, LF, OX, EL, MP;

// Timing
const int IDLETIMER = 20000;        // If no message received from KSP for more than 20s, go idle (default 2000)
const int CONTROLREFRESH = 10;      // Send control packet every 10 ms (default 25)
const int stageLedBlinkTime = 500;  // Blink staging LED when armed every 500 ms

// Variables used in timing
unsigned long deadtime, deadtimeOld, controlTime, controlTimeOld, stageLedTime, stageLedTimeOld;
unsigned long now;

// Variables used in serial communication
boolean Connected = false;
byte id;

// Other variables
long randomNumber;    // Random numer for welcome message


void setup() {
  
  randomSeed(analogRead(0));    // Init random()
  Serial.begin(38400);          // KSPSerialIO connection
  mySerial.begin(9600);         // LCD connection

  // Initializing controller
  controlsInit();               // Set all pin modes
  InitTxPackets();              // Initialize the serial communication
  if (!digitalRead(pPOWER))
    testLEDS(50);               // Blink every LED once to test (with a delay of 10 ms)
  
  //delay(500);                   // Wait for LCD boot
  //setLCDlight(157);             // Making sure LCD backlight is on
  //delay(500);

  // Initializing controller
  
  
  clearLCD();
  if (!digitalRead(pPOWER))
    welcomeMessage();           // LCD Welcome message

}

void loop() {
  
  if (digitalRead(pPOWER))
    shutControllerOff ();     // Controller is OFF

  if(!digitalRead(pMODE))
    debug_mode();             // Debug mode
  else {
    // KSP play mode
    get_vessel_data();        // Receive KSP data
    send_control_packet();    // Send data to KSP
  }

}
