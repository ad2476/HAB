High-Altitude Balloon
===
###### Arun Drelich

## Purpose

A payload will be delivered to and recovered from approximately 27’000m altitude. The purpose of this project is to take atmospheric gas measurements, record data on the payload in free-fall, and gain an understanding of high-altitude winds through calculations of the balloon’s trajectory over land.

## Flight Computer

The flight control system (FCS) consists of:

* Arduino Pro 5V as flight computer
* OpenLog + 8GB µSD card for data logging

On-board sensing of systems status will be added (i.e. ensuring all systems are functioning during flight, monitoring of battery levels).

## GPS/GSM System

The GPS system consists of an LS20031 66-channel GPS receiver connected via serial port expander. Data will be interpreted, logged and forwarded to the GSM module through the FCS.

The GSM module will send text messages of the balloon’s altitude and coordinates, battery status and other vital information.

## Sensors System

The sensors system will operate over either the I2C bus or through digital/analog input.

* BMP085 Barometric pressure sensor (for determining altitude)
* MMA7361 3-axis accelerometer
* LPY503AL Gyroscope
* MAG3110 3-axis magnetometer (I may have broken it)
* TMP36 temperature sensor
* LPG and CNG gas sensors

## Camera System

The camera system will likely consist of a Panasonic Lumix digital camera. The shutter will be triggered with a micro servo above the trigger button. Pictures will be stored on a 16GB µSD card.

Initial freezer tests indicate a battery life of 2 hours with a 600mAh battery. A 2000mAh battery will be tested next time.

## Heating System

Exterior temperatures will reach approximately -60ºC during flight. A heating system is necessary for continued functioning of the electronics. It shall consist of an independent system of two heating pads and two 850mAh batteries, toggled by the FCS when interior temperatures drop below 0ºC.

## Power Systems

In order to mitigate total systems failure due to drained batteries, the electronics are divided into four power systems:

* 4x 1.5V 3000mAh Energizer Lithium in series (6V nominal output): FCS, Sensors system, GPS system
  * Expected life: Not yet calculated, likely several hours - expect less due to effects of cold
* 2x 3.7V 2000mAh Li-ion in series (7.4V nominal output): GSM module
  * Expected life: Max. 1000h (only standby), Min. 5.7h (only GPRS transmission)
* 2x 3.7V 2000mAh Li-ion: Camera system (1 battery for video cameras, 1 battery for photo camera)
  * Expected life of video: Max. 20h (assuming 100mA draw) - expect less due to effects of cold
  * Expected life of photo: Max. 5.8h (assuming 345mA draw) - expect less due to effects of cold
* 2x 3.7V 850mAh Li-ion (7.4V nominal output): Heating system
  * Expected life: 1.2h (700 mA draw) - expect less due to effects of cold (only active if internal temp < 0º C)

## Ascent, Egress and Payload

Kaymont Balloons provides weather balloons. Ripstop chutes are an option for parachute sourcing. Helium will be used for lift. The payload container will be insulated with styrofoam and mylar.
Natural egress should occur around 27’000m when the balloon bursts.
