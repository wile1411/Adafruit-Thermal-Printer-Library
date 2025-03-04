/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates adding multiple custom character command for a DFRobot GY-EH402. 
  Might work for other small TTL thermal printers.
  See 'A_printertest' sketch for a more generalized printing example.

  THESE FEATURES ARE NOT AVAILABLE ON ALL PRINTERS.  Older firmware
  does not support the alternate characters used here.
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
  
  /* -----------------------------------------------------------------------
  12x24
  Six characters used to draw a box. TopLeft, Straight, TopRight, Vertical, BottomLeft, BNottomRight and a custom stack of boxes character.
  [Yes, I know box drawing characters exist in the extended character set, it's just an example for using this command]

  The below character format is the number 12 (0x0C) to indicate the width, then 36 characters that make up the pixel data.
  Pixel data has to be transposed (x values swapped with y values) for the thermal printer to read it correctly
  This transposition is why a 12 wide by 24 tall font is shown as 36 bytes (12 vertical slices of 3 bytes) or (12 bits by [3x8] 24 bits)

  PER character example     Most forum posts asking about this command miss the following detail.
  0x0C,                     <- This byte that indicates the next 12 groups of 3 bytes are a character
                            The above byte MUST be supplied for EACH character, but can be a different value per character
                            
  0x00,0x00,0x00,           1st vertical slice of 24 pixels (3 x 8bytes = 24 pixels)
  0x00,0x00,0x00,           2nd veritcal slice
  0x00,0x00,0x00,           3rd etc...
  0x00,0x0F,0xFF,
  0x00,0x1F,0xFF,
  0x00,0x38,0x00,
  0x00,0x70,0x00,
  0x00,0x61,0xFF,
  0x00,0x63,0xFF,
  0x00,0x67,0x00,
  0x00,0x66,0x00,
  0x00,0x66,0x00            next chacter after this line usually be 12 (0x0C) to start the next character data.

  The last line in the below boxBorderChars array is an example of a character not using the full width of 12 pixels.
  As is only 9 pixels wide as indicated by the first byte being a '9'. It is 3 vertical slices thinner (3 bytes each) so 9 bytes shorter than others in the array.
  */

    uint8_t boxBorderChars[] = {
        0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0x00,0x1F,0xFF,0x00,0x38,0x00,0x00,0x70,0x00,0x00,0x61,0xFF,0x00,0x63,0xFF,0x00,0x67,0x00,0x00,0x66,0x00,0x00,0x66,0x00,
        0x0C,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,
        0x0C,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x67,0x00,0x00,0x63,0xFF,0x00,0x61,0xFF,0x00,0x70,0x00,0x00,0x38,0x00,0x00,0x1F,0xFF,0x00,0x0F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF0,0x00,0xFF,0xF8,0x00,0x00,0x1C,0x00,0x00,0x0E,0x00,0xFF,0x86,0x00,0xFF,0xC6,0x00,0x00,0xE6,0x00,0x00,0x66,0x00,0x00,0x66,0x00,
        0x0C,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0xE6,0x00,0xFF,0xC6,0x00,0xFF,0x86,0x00,0x00,0x0E,0x00,0x00,0x1C,0x00,0xFF,0xF8,0x00,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x09,0x0F,0x00,0x1C,0x1F,0x00,0x78,0x7F,0x03,0xE0,0xFF,0x3F,0x80,0xFF,0xFE,0x00,0xFB,0xFC,0x00,0xF3,0xF0,0x00,0xE3,0xC0,0x00,0xC0,0x00,0x00
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
    printer.println(F("MULTIPLE USER DEFINED CHARACTER EXAMPLE\n"));
    printer.underlineOff();
  
    printer.userDefinedCharacter(3, 33, 39, 250, boxBorderChars);     // Add box characters to characters 33,34,35,36,37,38 & 39 ( ! " # & $ % ' )
    printer.userCharacterSetOn();                                     // Enable user-defined character set
    printer.setLineHeight(20);                                        // Adjust line height for the new characters to avoid gaps between carriage returns
    printer.println("!\"\"\"\"\"\"\"#");
    printer.println("& 'Box' &");                                     //Draw 'box' in a box with boxes using the characters we've replaced
    printer.println("$\"\"\"\"\"\"\"%");
    
    printer.feed(2);
    printer.setDefault(); // Restore printer to defaults
  }
  
  
  void loop() {
  }
  