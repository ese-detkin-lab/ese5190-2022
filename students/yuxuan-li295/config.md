### `/lab2b/part01/link`
- [Part01](https://github.com/anniepan8215/ESE519_lab2B/tree/main/lab/01_registers)


### `/lab2b/part01/status`
Complete
### `/lab2b/part02/link`
none
### `/lab2b/part02/status`
not-started
### `/lab2b/part03/link`
none
### `/lab2b/part03/status`
not-started
### `/lab2b/part04/link`
none
### `/lab2b/part04/status`
not-started
### `/lab2b/part05/link`
none
### `/lab2b/part05/status`
Completed.
# I2C on Oscilloscope
This part is for checking The I2C pins' waveforms on the oscilloscope. The python code in part1 firefly is running just in order to confirm that the I2C Just confirm that I2C communication is active (taking place) between the QT Py (KB2040 and sensor (APDS-9960). This can be done by flashinging the 'firefly' code on to the QT Py, which in ture is connected to the sensor (APDS-9960).
In this lab, we connect the first probe to SCL (CLK or clock) while the associated black wire to ground of the microcontroller. Similarly, the second probe is connected to SDA while the associated black wire to ground.
# Circuit Connection Setup  

<img src="Media\Circuit_Connection.jpg" style="zoom:70%"> <br> 
The corresponding waveform is given as:  
<img src="Media\Wave1.jpg" style="zoom:70%"> <br> 
<img src="Media\Wave2.jpg" style="zoom:70%"> <br> 
<img src="Media\Wave3.jpg" style="zoom:70%"> <br> 
<img src="Media\Wave4.jpg" style="zoom:70%"> <br> 

Code for python in this part:
```python
import board
import busio
import adafruit_apds9960.apds9960
import time
import neopixel
i2c = busio.I2C(board.SCL1, board.SDA1)
sensor = adafruit_apds9960.apds9960.APDS9960(i2c)
sensor.enable_proximity = True
sensor.enable_color = True
pixels = neopixel.NeoPixel(board.NEOPIXEL, 1)
sensor.color_integration_time = 10
clast = 0
while True:
    r, g, b, c = sensor.color_data
    print(c)
    if(c > clast+5):
        pixels.fill((255,0,0))
    else:
        pixels.fill((0,0,0))
    clast = c
    time.sleep(0.05)


```  

### `/lab2b/part06/link`
none
### `/lab2b/part06/status`
not-started
### `/lab2b/part07/link`
none
### `/lab2b/part07/status`
not-started
### `/lab2b/part08/link`
none
### `/lab2b/part08/status`
not-started
### `/lab2b/part09/link`
none
### `/lab2b/part09/status`
not-started
### `/lab2b/part10/link`
none
### `/lab2b/part10/status`
not-started
### `/lab2b/status`
not-started
