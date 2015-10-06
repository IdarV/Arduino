# Rapport for Exam01
##### By Idar Vassdal (tjoida)
 
## The program
This is a text-scrolling program that uses the package LedControl, that are referenced below, to control a 8x8 matrix. 
The default text is "hello", but it will display input to the Serial console (characters a-z).
I looked into another Led driver, also referenced below, but I decided to go for LedControl because it looked much simpler, and had better readability.

## Video

Demo of me using the device with input into the Serial console

https://www.youtube.com/watch?v=lXrRxu93aIw&feature=youtu.be

## Files included
- *Text_scrolling* is the Arduino program. Requires you to have LedControl in your local Arduino Library.
- *Sketch_pdf* is a overview of how to set up the arduino with the hardware, made with Fritzing
- *smm_1588asrg_OVERVIEW.png* is my cheat-sheet, I included it because why not?

## LED PACKAGE
- LedControl package 	https://github.com/wayoda/LedControl
- How to use LedControl 		https://tronixstuff.files.wordpress.com/2010/07/matrixschematic2.jpg
- Did not go for		https://github.com/marcmerlin/LED-Matrix/blob/master/examples/directmatrix8x8/directmatrix8x8.ino

## OTHER INFORMATION
##### MAX7219:
- Datasheet	http://www.adafruit.com/datasheets/MAX7219.pdf
- Led Driver Demo http://tronixstuff.com/2013/10/11/tutorial-arduino-max7219-led-display-driver-ic/

##### Resources:
- 2D array in C++ 		https://gsamaras.wordpress.com/code/dynamic-2d-array-in-c/
- Font inspired by 	http://www.fontriver.com/font/lightdot_8x8/