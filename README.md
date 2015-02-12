# ArduinoNano-ESP8266
This is a little project I made to read a couple of temperatures.
These temps are posted to thingspeak and displayed on a lcd screen.

<h2>Installation</h2>
<h3>ESP8266</h3>
| ESP8266 pin | Arduino pin | External 3V3  |
| ----------- | ----------- | ------------- |
| RXD         | D2          | -             |
| TXT         | D3          | -             |
| VCC         | -           | 3v3           |
| GND         | GND         | GND           |
| CH_PD       | -           | 3v3           |

<h3>LCD</h3>
| LCD | Arduino pin | External 5V |
| --- | ----------- | ----------- |
| RS  | D4          | -           |
| E   | D5          | -           |
| D4  | D6          | -           |
| D5  | D7          | -           |
| D6  | D8          | -           |
| D7  | D9          | -           |
| GND | GND         | GND         |
| Vin | -           | 5V          |

Also 
- Wire the backlight GND to GND of external 5V
- Wire the backlight Vin to 1k Resistor to Vin
- Wire a 1k potentiometer between Vin and Contrast Voltage
- Wire RW to GND

<h3>Arduino</h3>
| Arduino | External 3V3  | External 5V |
| ------- | ------------- | ----------- |
| GND     | GND           | GND         |
| VIN     | -             | 5V          |

<h2>Code changes</h2>
To connect to a WiFi spot put your SSID and password in the correct place.<br>
Also your API key has to be inserted in the correct place.<br>
If you have more channels or fields at thingspeak you have to change the GET request.

<h2>Note</h2>
You have to figure out for yourself how to wire your thermometers
Also you have to figure out the formula for the thermometer
