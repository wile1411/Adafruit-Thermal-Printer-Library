/*------------------------------------------------------------------------
  Example sketch for DFRobot GY-EH402 Thermal Printer library for Arduino.
  Demonstrates adding a custom character. 
  Might work for other small TTL thermal printers.
  See 'A_printertest' sketch for a more generalized printing example.
  ------------------------------------------------------------------------*/

  #include "Adafruit_Thermal.h"

  // Here's the syntax when using SoftwareSerial (e.g. Arduino Uno) --------
  // If using hardware serial instead, comment out or remove these lines:
  
  #include "SoftwareSerial.h"
  #define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
  #define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer
  
  SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
  Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
  // Then see setup() function regarding serial & printer begin() calls.
  
  // Here's the syntax for hardware serial (e.g. Arduino Due) --------------
  // Un-comment the following line if using hardware serial:
  
  //Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.
  
  // -----------------------------------------------------------------------
  // 12x24 Flower Character
  uint8_t flowerCharacter[] = {
    0x0C,
    0x06,0x00,0x00,
    0x0F,0x01,0x80,
    0x39,0x83,0xC0,
    0x24,0xC1,0xE0,
    0x6E,0x60,0x20,
    0xDB,0x3F,0xFF,
    0xB1,0xBF,0xFF,
    0xDB,0x20,0x80,
    0x6E,0x63,0x80,
    0x24,0xC7,0x00,
    0x31,0x86,0x00,
    0x1F,0x00,0x00
};
  
  
  void setup() {
  
    // This line is for compatibility with the Adafruit IotP project pack,
    // which uses pin 7 as a spare grounding point.  You only need this if
    // wired up the same way (w/3-pin header into pins 5/6/7):
    pinMode(7, OUTPUT); digitalWrite(7, LOW);
  
    mySerial.begin(9600);  // Initialize SoftwareSerial
    //Serial1.begin(9600); // Use this instead if using hardware serial
    printer.begin();       // Init printer (same regardless of serial type)
  
    printer.underlineOn();
    printer.println(F("SINGLE USER DEFINED CHARACTER EXAMPLE\n"));
    printer.underlineOff();
    
    //printer.userCharacterSetOff();                     // User-defined character set is Off by Default
    printer.userDefinedCharacter(3, 33, 33, 37, flowerCharacter);   // Replace the '!' character char(33) with a flower.
    printer.println("There is no flower!");              // Still shows '!' as user-defined character set not enabled
    
    printer.userCharacterSetOn();                        // Enable user-defined character set
    printer.println("!!! Flowers !!! everywhere !!!");   // Smell the flowers

    printer.clearUserCharacter(33);                      // Clear the user-defined character for char 33
    printer.println("Where is my Flower?!");             // user-defined character set still enabled, but there is no longer any user-defined data for char 33

    printer.feed(2);
    printer.setDefault(); // Restore printer to defaults
  }
  
  
  void loop() {
  }
  