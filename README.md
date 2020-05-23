# MinimalLamp
## About

 The title says it all. This project has the objective to be a code for development of simple LED lamps. The idea of it is to allow developers and artists to have libraries of different colors, animations and functions so that the implementation of LED lamps is easier. 
 
 This README is still to be updated, this text refers to the [MinimalLamp](https://github.com/HenriqueOz/MinimalLamp, "Check it out!")

## Code explained

 For this particular project I am using the Arduino feature of tabs, ie, several .ino files that work together as one. Currently there is the following tabs:

### MinimalLamp.ino 

 This is the main file of the project. It contains the libraries being used and has most of the main variables declarations. It also includes the setup() function of this arduino code. 
 
### Pallets.ino 
 This file contains all the pallets of the code. A pallet, in order to be used, needs to be declared on the enum palletes_mode on the **MinimalLamp.ino** file. Once the pallet is declared, it will accesible by the main Serial menu. Don't forget to update the *number_of_palletes*
 
### RGB_animations.ino 
This file contains all the animations performed in the RGB color space. The animations use the colors described in the selected pallet. A new animation, in order to be available on the Serial menu, it needs to be declared on the enum *animation_modes* on the **MinimalLamp.ino** file. Don't forget to update the *number_of_modes*

### HSV_animations.ino 
This tab still has to adapted to be accesible via the Serial menu. It is basically the examples available on the **Adafruit_NeoPixel** library. 

### update_handlers.ino 
This tab is where the magic happens. It has two functions: 
#### update_palletes() 
*Update_palletes* directs the code to use a determined pallet selected by the user on the Serial Menu. 
#### update_strip() 
*Update_strip* directs the code to use a determined animation selected by the user on the Serial Menu. 

### z_main_loop.ino 
This tab contains the main loop function of the arduino. It basically contains the Serial Menu handler. The Serial hander has functions determined by letters where the user can select the brightness of the LEDS, the speed of the animation, the animation itself, the pallet of colors and to turn off the lamp. 

* q to turn off the lamp 
* w to select an animation "above"
* s to select an animation "below" 
* a to reduce the speed of the animation
* d to increase the speed of the animation
* i to reduce the speed of the animation a lot
* o to increase the speed of the animation a lot\n
* j to select an palette "above" 
* k to select an palette "below"
* n to reduce the brightness of the LED lamp 
* m to increase the brightness of the LED lamp 
* z to display the current configuration on the Serial interface 
* x to show this help

The tab is named as z_\* because the Arduino needs to reach this tab at the end so that all variables were declared before its compilation. 

## Hardware 

One of the main characteristics desired for this project is that it needs to have a simple configuration regarding the hardware. The hardware used on this project were: 
* A simple [Arduino Nano (ATMega 328P)](https://store.arduino.cc/usa/arduino-nano "Arduino page") or an ESP 8266. The objective of the ESP is to enable WiFi capabilities that are described in this other branch of the project: (TBD).
* WS2812 LEDs with update frequency of 800 KHz. I bought my LEDs from this [Aliexpress supplier](https://www.aliexpress.com/item/32682015405.html?spm=a2g0s.9042311.0.0.739a4c4dKD8sVe "Not an affiliate link")
* An old smartphone power supply 

Some notes: 

**Be careful**, since depending on the amount of LEDs, the drained current might exceed the maximum rated for your USB port, thus leading to *magic smoke*

Remember to commonize the ground of your external power supply with the USB ground. The USB ground will be available on any Arduino ground pin.

Use the defines *LED_PIN* and *LED_COUNT* accordingly to your setup. Basically any Arduino pin might be used. Update the type of your LED accordingly to the Adafruit_NeoPixel library 

A 330 ohms resistor in-between the arduino data pin and the beginning of the LED strip helps to reduce peak current damage to the first LED 

It is advisable to use a large capacitor between the VCC and ground of your suplply, as close as possible to LEDs, for a smooth operation. 

If your LED strip is very long, consider supplying energy at more than one point. 	

To use the ESP you need to use the pin 4 on your arduino code. The ESP has a really convoluted way to set pins and their exclusive functionality so check a tutorial somewhere. I used this one [NodeMCU ESP8266: Detalhes e Pinagem](https://www.youtube.com/watch?v=slKGGrPDNpk "Youtube") which is in Portuguese.


## Next steps 

The roadmap for new features for this projects are:
* [ ] Create animations using the HSV color space 
* [ ] Add static or low speed animations 
* [ ] Add another form of communication (bluetooth, wifi, etc) for final implementation
* [ ] Add more colors 
* [ ] Improve code performance, ie, reduce memory usage at maximum 
* [ ] Add video and images of the Lamp fucntioning