#!/usr/bin/env python3

#####################################################
import mfrc522
import utime
from servo import Servo
from machine import I2C,Pin
from ssd1306 import SSD1306_I2C  

makerobo_ObstaclePin = 15       

led_onboard = machine.Pin(25,machine.Pin.OUT)

sck = 6
mosi = 7
miso = 4
cs = 5
rst = 22
s1 = Servo(2)      

#oled
i2c=I2C(0,sda=Pin(0), scl=Pin(1), freq=400000) 
oled = SSD1306_I2C(128, 64, i2c) 
oled.fill(1) 

oled.show()
oled.fill(0)
oled.show()

oled.text("Hello World!",0,9,1)
oled.text("Makerobo Kit!",0,18,1)
oled.show()
#oled

#HW
def makerobo_setup():
    global ir_Obstacle
  
    ir_Obstacle = Pin(makerobo_ObstaclePin,Pin.IN,Pin.PULL_UP)
#hw


#servo
def makerobo_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


def servo_Angle(angle):
    if angle < 0:
        angle = 0
    if angle > 180:
        angle = 180
    s1.goto(round(makerobo_map(angle,0,180,0,1024)))


def do_write():
    rdr = mfrc522.MFRC522(sck=sck, mosi=mosi, miso=miso, rst=rst, cs=cs)
    try:
        while True:
            if (0 == ir_Obstacle.value()):
                led_onboard.value(1) 
            else:
                led_onboard.value(0) 
            
            (stat, tag_type) = rdr.request(rdr.REQIDL)
            if stat == rdr.OK:
                (stat, raw_uid) = rdr.anticoll()
                if stat == rdr.OK:
                    print("Card detected")
                    print("  - uid  : 0x%02x%02x%02x%02x" % (raw_uid[0], raw_uid[1], raw_uid[2], raw_uid[3]))
                    if raw_uid[0] == 0x61 and  raw_uid[1] == 0x20 and  raw_uid[2] == 0x34 and  raw_uid[3] == 0x47:
                        print("Card Right! Welcom!")
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("Card Right!",0,9,1)
                        oled.text("Door Open!",0,18,1)
                        oled.show()
                        servo_Angle(150)
                        utime.sleep(5)
                        servo_Angle(0)
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("Hello!",0,9,1)
                        oled.text("Door Close!",0,18,1)
                        oled.show()
                    else:
                        print("Card Error! Try Again!")
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("Try Again!",0,9,1)
                        oled.text("Door Close!",0,18,1)
                        oled.show()
                        servo_Angle(0)
        utime.sleep(0.05)

    except KeyboardInterrupt:
        print("Bye")



if __name__ == '__main__':
    makerobo_setup() 
    oled.fill(1)
    oled.show()
    oled.fill(0)
    oled.show()
    oled.text("Hello!",0,9,1)
    oled.text("Door Close!",0,18,1)
    servo_Angle(0)
    oled.show()
    do_write()

        

