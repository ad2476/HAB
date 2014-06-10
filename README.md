High-Altitude Balloon
===
###### Arun Drelich

## Purpose

A payload will be delivered to and recovered from approximately 30’480m (100'000ft) altitude. The purpose of this project is to take atmospheric gas measurements, record data on the payload in free-fall, and gain an understanding of high-altitude winds through post-flight calculations of the balloon’s trajectory over land.

## Flight Computer

The flight control system (FCS) consists of:

* Arduino Pro 3.3V as flight computer
* OpenLog + 8GB µSD card for data logging

On-board sensing of systems status will be added (i.e. ensuring all systems are functioning during flight, monitoring of battery levels).

## GPS/GSM System

The GPS system consists of an LS20031 66-channel GPS receiver connected via serial port expander. Data will be interpreted, logged and forwarded to the GSM module through the FCS.

The GSM module will send text messages of the balloon’s altitude and coordinates, and other vital information.

## Sensors System

The sensors system will operate over either the I2C bus or through digital/analog input.

* BMP180 Barometric pressure sensor (for determining altitude)
* MMA7361 3-axis accelerometer
* LPY503AL Gyroscope
* MAG3110 3-axis magnetometer (I may have broken it)
* TMP36 temperature sensor
* Thermistor 10K
* LPG and CNG gas sensors

## Camera System

The camera system will likely consist of a Panasonic Lumix digital camera. The camera will take pictures in burst mode (1 Hz) until the 32GB µSD card runs out of space - approximately 2h of HD photographs.

Initial freezer tests indicate a battery life of 2 hours with a 600mAh battery. A 2000mAh battery will be tested next time.

Additional video cameras in the form of two keychain 808 cameras attached to a 2000mAh battery will film the flight.

## Heating System

Exterior temperatures will reach approximately -60ºC during flight. A heating system is necessary for continued functioning of the electronics, and should hopefully constrain temperatures above -20ºC. It shall consist of an independent system of two heating pads and 4 AA Lithium batteries in series, and shall operate continuously.

## Power Systems

In order to mitigate total systems failure due to drained batteries, the electronics are divided into four power systems:

1. **3x 1.5V 3000mAh Energizer Lithium Ultimate (4.5V nominal output)**: FCS, Sensors system, GPS system
  * Expected life: Not calculated, likely several hours - expect fewer due to effects of cold
2. **2x 3.7V 2000mAh Li-ion in series (7.4V nominal output)**: GSM module
  * Expected life: Max. 1000h (only standby), Min. 5.7h (only GPRS transmission), expect fewer due to cold
3. **1x 3.7V 2000mAh Li-ion**: Camera system (1 battery for video cameras, 1 battery for photo camera)
  * Expected life: Max. 4.5h (assuming 445mA draw) - expect fewer due to effects of cold
4. **4x 1.5V 3000mAh Energizer Lithium Ultimate (6V nominal output)**: Heating system
  * Expected life: 4h (700 mA draw) - expect fewer due to effects of cold (active throughout)

With an expected flight duration of 2.8±0.5h, this should be plenty of battery capacity, even accounting for the effects of cold. Freezer tests will be run well in advance of launch to determine true capacity.

## Ascent, Egress and Payload

Kaymont Balloons provides weather balloons. Parachute purchased from the-rocketman.com. Helium will be used for lift. The payload container will be insulated with styrofoam and mylar, and be cushioned with various forms of foam.
Natural egress should occur around 33’000m (100'000ft) when the balloon bursts. Payload mass will be approximately 1.2 kg.
