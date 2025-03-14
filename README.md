# Adafruit Thermal Printer Library 
(Amended for DFRobot Thermal Printer)


[![Build Status](https://github.com/adafruit/Adafruit-Thermal-Printer-Library/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit-Thermal-Printer-Library/actions)[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit-Thermal-Printer-Library/html/index.html)


This is an Arduino library for the Adafruit Thermal Printer.
Pick one up at --> https://www.adafruit.com/product/597
These printers use TTL serial to communicate, 2 pins are required.

[Amended library for the DFRobot GY-EH402 Thermal printer available at --> https://www.dfrobot.com/product-1799.html]

Since Adafruit has abandoned this library to archive, I've been doing some deep dives into the DFRobot printer and created this fork for my notes on that printer model and to contribute to those looking to use a similar thermal printer.
This fork includes added functionality that I saw a number of people having issues implementing.

Full tutorial with wiring diagrams, images, etc. is available at:
https://learn.adafruit.com/mini-thermal-receipt-printer

Before loading the example code, or even opening the Arduino software,
place the Adafruit_Thermal folder in your Arduino library.

////ARDUINO LIBRARY LOCATION////
On your Mac:: In (home directory)/Documents/Arduino/Libraries
On your PC:: My Documents\Arduino\libraries
On your Linux box: (home directory)/sketchbook/libraries

Adafruit invests time and resources providing this open source code.  Please support Adafruit and open-source hardware by purchasing products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community.  Originally based on Thermal library from bildr.org
MIT license, all text above must be included in any redistribution.
