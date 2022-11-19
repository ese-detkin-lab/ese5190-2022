# TODO: #
* use your Lab 1 firefly code to generate ADPS9960 I2C traffic and display it on a lab oscilloscope
take a screenshot of some portion of this exchange, and figure out/annotate what's happening based on the protocol documentation in the ADPS9960 datasheet

# I2C Traffic #

As we can see from the graphics, I2C is a serial, synchronous communication protocol, as the SCL or clock signal drives communication between the nodes.

The oscilloscope was set to digital mode (without noise) to get a better output signal.

We use conventional probes and logic analyzer probe cables to view the digital signal on the oscilloscope.

The I2C traffic between the Adafruit QTPy RP2040 and the APDS9960 sensor is depicted in the gif attached.


