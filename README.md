# ArduinoNano-ESP8266
This is a little project I made to read a couple of temperatures.<br>
The temps that have been read are posted to thingspeak and displayed on a lcd screen.

<h2>Installation</h2>

<h3>Pinning</h3>

| Arduino | ESP8266 | LCD | External 3V3  | External 5V |
| ------- | ------- | --- | ------------- | ----------- |
| GND     | GND     | GND | GND		        | GND	        |
| VIN     | -       | VIN	| -		          | 5V		      |
| D2     	| RXD     | -	  | -		          | -		        |
| D3     	| TXD     | -	  | -		          | -		        |
| D4     	| -       | RS	| -		          | -		        |
| D5     	| -       | E	  | -		          | -		        |
| D6     	| -       | D4	| -		          | -		        |
| D7     	| -       | D5	| -		          | -		        |
| D8     	| -       | D6	| -		          | -		        |
| D9     	| -       | D7	| -		          | -		        |
| -		    | VCC		  | -	  | 3V3		        | -		        |
| -		    | CH_PD		| -	  | 3V3		        | -		        |

Note on LCD
- Wire the backlight GND to GND of external 5V
- Wire the backlight Vin to 1k Resistor to Vin
- Wire a 1k potentiometer between Vin and Contrast Voltage
- Wire RW to GND

<h3>Code changes</h3>
To connect to a WiFi spot put your SSID and password in the correct place.<br>
Also your API key has to be inserted in the correct place.<br>
If you have more channels or fields at thingspeak you have to change the GET request.

<h2>Note</h2>
You have to figure out for yourself how to wire your thermometers<br>
Also you have to figure out the formula for the thermometer
