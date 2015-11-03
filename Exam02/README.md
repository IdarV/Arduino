# Embedded Systems, exam02: alarm clock.
###### by idarv

## The program
The Arduino uses a a RTC(Real Time Clock) chip, DHT11 sensor, speaker, PS2 joystick, and a LCD screen to make an alarm-clock.
The screen displays, from top left reading right
- Month
- Day of month
- Temperature in Celsius
- Temperature in Fahrenheit
- Humidity
- Clock (HH:MM:SS)
- Week-day
- Year

#### How it works
The functionality is pretty basic. The interface updates every second. When the joystick is pressed, a set-the-alarm mode is entered, and you can use the joystick to navigate between hours, minutes and seconds. Once you have the time you want the alarm on, simply press the joystick again and the alarm is set. Once the alarm goes off, you have to press the button on the board to disable it.

The code has alot of comments on how the specific parts work.

Youtube video of the clock in action:

#### What I focused on
The arduino Uno has slow SPI speeds, the LCD screen is slow to update. This causes flickering when updating,  and if the whole screen is updated at once it will look.. bad. That's why I decided to use as dynamic updates as possible, only updating the parts of the screen that actually changes. This means that, yes, the year will only update once every 365 days.

I wanted to make the clock as accurate as possible, so I went from ```delay(1000)``` to waiting for the RTC to gain a new second. The reason was because the execution in each loop took some ms *(i.e. 100ms)*, so the delay was delayed *(now uses 1100 ms. for each loop)* and the clock was off, which resulted in the clock sometimes skipping a second *(now every 1000/100 == 10 second)*. Reading from the DHT11 sensor is what takes the longest.

#### Libraries
###### RTClib
https://github.com/adafruit/RTClib \
Realtime Clock Library for Arduino. I chose this because it had a lot of code examples, and seemed fairly easy to use.

###### TFT and SPI
Built-in Arduino Libraries. TFT is for communicating with TFT-LED-screens, and it's compatible with the screen I use for this project. SPI is simply for communicating with peripheral devices, and is required by TFT.

###### DHT
http://learn.adafruit.com/dht/downloads \
DHT library for Arduino. I chose this because I had used it in lectures before, and it seems that alot of people are using it.

## Sources
http://42bots.com/tutorials/arduino-joystick-module-example/
The RTCLib example ```RTCLib::ds1307```

## Final words
Please use this sentence as a quote instead of something from Fredrick's note.

TODO:
- Fritzing
- Complete the README
- Video
