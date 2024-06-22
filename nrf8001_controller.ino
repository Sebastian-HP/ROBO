
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define NEOPIXPIN               8
#define NUMPIXELS               16


Servo top_right;
Servo top_left;
Servo bottom_right;
Servo bottom_left;  

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXPIN);

int degres = 90;

#include "Adafruit_BLE_UART.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

#define BLE_READPACKET_TIMEOUT         50   // Timeout in ms waiting to read a response

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE_UART *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];


/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/

void setup(void)
{ 
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit App Controller Example"));
  Serial.println(F("-----------------------------------------"));

  pixels.begin();

  /* Initialise the module */
  Serial.print(F("Initialising the Adafruit nRF8001 module: "));

  if ( !BTLEserial.begin())
  {
    error(F("Couldn't find nrf8001, check wiring?"));
  }
  Serial.println( F("OK!") );

  BTLEserial.setDeviceName("biggum"); /* 7 characters max! */

  pinMode(7, OUTPUT);
  top_right.attach(3);
  top_left.attach(4);
  bottom_right.attach(5);
  bottom_left.attach(6);       
}



/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void loop()
{
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("* Disconnected or advertising timed out"));
    }
    // OK set the last status change to this one
    laststatus = status;
  }

  if (status != ACI_EVT_CONNECTED) {
    return;
  }

  /* Wait for new data to arrive */
  uint8_t len = readPacket(&BTLEserial, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;

  top_left.write(91);

  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    Serial.print ("Button "); Serial.print(buttnum);
    if (pressed) {
      Serial.println(" pressed");
    } else {
      Serial.println(" released");
    }
    
   if (buttnum == 8 and pressed) {
    top_right.write(180);
    top_left.write(180);
    bottom_right.write(180);
    bottom_left.write(180);  


       
     }

   if (buttnum == 7 and pressed) {
    top_right.write(0);
    top_left.write(0);
    bottom_right.write(0);
    bottom_left.write(0);

      
     }

    if (buttnum == 5 and pressed) {
      top_right.write(180);
      top_left.write(0);
      bottom_right.write(180);
      bottom_left.write(0); 
 
     }

    if (buttnum == 6 and pressed) {
      top_right.write(0);
      top_left.write(180);
      bottom_right.write(0);
      bottom_left.write(180);
      
     }

  if (buttnum == 3 and pressed) {

      
     }

  if (buttnum == 4 and pressed) {


     }


  if (buttnum == 1 and pressed) {
    top_right.write(89);
    top_left.write(90);
    bottom_right.write(90);
    bottom_left.write(90);

  }

  if (buttnum == 2 and pressed) {
    digitalWrite(7, HIGH);



  }

    

  }
  
}
