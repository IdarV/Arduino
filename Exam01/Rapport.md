# Rapport for Exam01
##### By Idar Vassdal (tjoida)
 
==================

Text-scrolling uses the package Led-Control that are referenced below. 
It's a simple program that scrolls text on the 8x8 matrix of what you write to the Serial console (a-Z).
I looked into another Led driver, but I decided to go for LedControl because it looked much simpler, and had better readability.

## Video

Demo of me using the device with input into the Serial console

https://www.youtube.com/watch?v=lXrRxu93aIw&feature=youtu.be

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