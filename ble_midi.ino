#include <Arduino.h>
#include <SPI.h>
#include <MIDI.h>
//#if not defined (_VARIANT_ARDUINO_DUE_X_)
//#include <SoftwareSerial.h>
//#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLEMIDI.h"

#include "BluefruitConfig.h"

#define LOAD_TEST_MS 10

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.7.0"


// Create the bluefruit object, either software serial...uncomment these lines
/*
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                              BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);
*/

/* ...or hardware serial, which does not need the RTS/CTS pins. Uncomment this line */
// Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

/* ...software SPI, using SCK/MOSI/MISO user-defined SPI pins and then user selected CS/IRQ/RST */
//Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_SCK, BLUEFRUIT_SPI_MISO,
//                             BLUEFRUIT_SPI_MOSI, BLUEFRUIT_SPI_CS,
//                             BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

Adafruit_BLEMIDI midi(ble);

bool isConnected = false;

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// callback
void connected(void)
{
  isConnected = true;
  
  Serial.println(F(" CONNECTED!"));
  
//  Serial.print(F("LOAD TESTING MAJOR C CHORD @ "));
//  Serial.print(LOAD_TEST_MS);
//  Serial.println(F(" MS."));
//  Serial.println();
//  delay(1000);
//
//  Serial.println(F("HOLD ONTO YOUR BUTTS."));
}

void disconnected(void)
{
  Serial.println("disconnected");
  isConnected = false;
}

void midiMsg(byte cmd, byte data1, byte data2) {
 Serial.write(cmd);
 Serial.write(data1);
 Serial.write(data2);
}

void BleMidiRX(uint16_t timestamp, uint8_t status, uint8_t byte1, uint8_t byte2)
{
  midiMsg(status,byte1,byte2);
//  Serial.print("[MIDI ");
//  Serial.print(timestamp);
//  Serial.print(" ] ");

  if ( byte2 == 127 ) {
    digitalWrite(13, HIGH);
  }
  if ( byte2 == 64 ){
    digitalWrite(13, LOW);
  }
//
//  Serial.print(status, HEX); Serial.print(" ");
//  Serial.print(byte1); Serial.print(" ");
//  Serial.print(byte2); Serial.print(" ");
//  
//  Serial.println();
}  

void setup(void)
{
//  while (!Serial);  // required for Flora & Micro
//  delay(500);

  Serial.begin(32500);

  // Flash LED on MIDI input
  pinMode(13, OUTPUT);

//  Serial.begin(115200);
//  Serial.println(F("Adafruit Bluefruit MIDI Example"));
//  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
//  Serial.print(F("Initialising the Bluefruit LE module: "));
  ble.begin(VERBOSE_MODE);
  ble.echo(false);
  ble.verbose(false);
  ble.sendCommandCheckOK(F("AT+GAPDEVNAME=Feather"));

  /* Set BLE callbacks */
  ble.setConnectCallback(connected);
  ble.setDisconnectCallback(disconnected);

  // Set MIDI RX callback
  midi.setRxCallback(BleMidiRX);
  
  midi.begin(true);
}

void loop(void)
{
  // interval for each scanning ~ 500ms (non blocking)
  ble.update(500);
  
  if ( isConnected )
  {
    uint8_t multiple_event[] = { 0x30, 0x64, 0x34, 0x64, 0x37, 0x64 };
    
    // Note ON
    //midi.send(0x90, 0x30, 0x64);
    //midi.send_n(0x90, multiple_event, 6);
    //delay(LOAD_TEST_MS);

    // Note OFF
    //midi.send(0x80, 0x30, 0x64);
    //midi.send_n(0x80, multiple_event, 6);
    //delay(LOAD_TEST_MS);
  }
}
