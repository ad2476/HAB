HAB Launch Summary
=========

Here's a quick overview of what this project is, as well as details about Launch Day.

###Dates:
* **Primary launch date**: 14.06.14
* *Possible backup date*: 20.06.14

###Possible Launch sites:

Listed in order of proximity to Greenwich

* 942-960 Noxon Road, Lagrangeville, NY (41.6439, -73.7985)
* 353 Gretna Road, Hyde Park, NY (41.7767, -73.8455)
* 63 Forest Drive, Hyde Park, NY (41.8123, -73.8966)
* Dinsmore Park, Staatsburg, NY (41.8473, -73.9306)
* 1750 Farm to Market Road, Coxsackie, NY (42.3355, -73.8149)

###Launch Day Schedule:
* **08:00**  Leave Greenwich
* **10:00** Arrive at launch site
* **10:00-11:00** Set up for launch: Inflate balloon, initialise and verify systems, seal box, etc.
* **11:00** Launch balloon
* **11:00-14:00** Drive to predicted landing site, eat lunch
* **14:00 onwards** Recovery of the payload. Ideally this can be accomplished within an hour

###What's going up:
The payload consists of: three cameras, a GPS unit, a GSM unit, an Arduino and various sensors, a heating system, and plenty of batteries. For a detailed overview of the project, see: https://github.com/ad2476/HAB.

###The setup:
The flight package consists of three major components: 
**Payload box**, **Parachute**, and **Balloon**.

####*The Payload Box*:
The box is constructed out of 6 rectangles insulating hard styrofoam, which are reinforced and held together through supporting wooden dowels and aluminum tape. Inside, foam padding on all sides keeps the payload cushioned and provides additional insulation against the frigid exterior (expecting outside temperatures of around -60°C). All electronics will be placed in the remaining space. 
####*The Parachute*:
The parachute is a nylon chute that will be attached via a 50lb fishing line to the payload box. It will then, in turn, be attached from the top to the balloon neck (also via a 50lb fishing line). In this sense, it will "connect" the payload with the balloon, and will be ready to open when the balloon pops.

####*The Balloon*:
The balloon is an 800-gram latex balloon from Kaymont Consolidated. It will be filled with around  2.7 $ m^3 $ of Helium, which will provide enough lift to carry the payload to an altitude of 30'500m (100'000ft) in around 2h.

###Tracking and Recovery:
On board the payload are a GPS unit and a GSM unit. The FCS (Flight Control System - an Arduino Pro w/ atmega328 microcontroller) communicates over a serial connection with the GPS, formats the NMEA sentences into a text message, and sends the message to the GSM unit via serial connection. 
If there's reception, the GSM unit will then send an SMS to a Google Voice number. Google voice allows text messages to be converted into emails. A python script on the tracking laptop checks the inbox for new texts from the payload every 20s (the payload broadcasts its location every 60s when it has GSM reception). The script processes the message and formats it into latitude and longitude coordinates readable by Google Maps/Earth or another service.

*Formatted SMS structure*: `[Timestamp (UTC)] / [Latitude] [Longitude] / [Altitude] / [Speed] `

*Parsed script output*: ` [Latitude] [Longitude] [Altitude] `

###Data Recording:
The FCS and its various sensors will be recording certain data during flight. These data will then be logged to a 4GB micro-SD card. The data recorded are:

* Exterior temperature and pressure - Also used as backup altimeter
* GPS timestamp (UTC), coordinates, altitude

*Data logging format*: `[UTC time] | [Latitude] [Longitude] | [GPS altitude] | [Speed] | [Pressure] [Barom. Altitude] | [Exterior temp]` 
