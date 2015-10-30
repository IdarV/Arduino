# Embedded Systems, exam02
###### by idarv

## The program
The program uses an Arduino One, a RTC(Real Time Clock) chip, PS2 joystick, and a LCD screen to make an alarm clock. The screen displays Month, day of month, hour, minute, second, day (i.e. friday) and year. If the PS2 button is pressed, an alarm can be set.

#### What I focused on
The screen we got is not fast to update, because the Arduino works as a bottleneck in the updating speed. That's why I started off with dynamically updating the screen which allowed me to only update the part of the screen that actually changes. This makes the update much smoother, and you really can't notice any flickering.

I wanted to make the clock as accurate as possible, so I went from ```delay(1000)``` to waiting for the RTC to gain a new second. The reason was because the execution in each loop took some ms *(i.e. 4ms)*, so the delay was delayed *(now 1004 for each loop)* and the clock was off, which resulted in the clock sometimes skipping a second *(now every 1000/4 == 250 second)*.

#### Libraries
###### RTClib
https://github.com/adafruit/RTClib \
Realtime Clock Library for Arduino. I chose this because it had a lot of code examples, and seemed fairly easy to use. I'm pretty happy with how it worked.

###### TFT && SPI
Built-in Arduino Libraries. TFT is for communicating with TFT-LED-screens, and it's compatible with the screen I use for this project. SPI is simply for communicating with peripheral devices, and is required by TFT. 

## Sources
http://42bots.com/tutorials/arduino-joystick-module-example/

TODO:
- Fritzing
- Complete the README
- Video
