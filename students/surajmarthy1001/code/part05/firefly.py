import time
import board
import neopixel
from adafruit_apds9960.apds9960 import APDS9960
from adafruit_apds9960 import colorutility

pixels = neopixel.NeoPixel(board.NEOPIXEL, 1)
i2c = board.I2C()
apds = APDS9960(i2c)
apds.enable_color = True
apds.color_integration_time=1
apds.color_gain=3


while True:
    # wait for color data to be ready
    while not apds.color_data_ready:
        time.sleep(0.5)

    # get the data and print the different channels
    r, g, b, c = apds.color_data
    print("light lux {}".format(colorutility.calculate_lux(r, g, b)))
    #Color intensity dependent Neopixel dimming
    lux_value = colorutility.calculate_lux(r,g,b)
    print(lux_value)
    #Map the light intensity to the brightness of the RGB Neopixel LED
    pixels.fill((r/4,g/4,b/4))
    time.sleep(0.1)