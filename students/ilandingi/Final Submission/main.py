#!/usr/bin/env python3

#####################################################
import mfrc522
import utime
from servo import Servo
from machine import I2C,Pin
from ssd1306 import SSD1306_I2C
from machine import Pin, PWM
from time import sleep
from machine import Pin,ADC


makerobo_photo = 0
makerobo_ObstaclePin = 15       

led_onboard = machine.Pin(18,machine.Pin.OUT)

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


red_pin = 11
green_pin = 12
blue_pin = 13

# setup the PWM for the RGB LED
p_R = PWM(Pin(red_pin))  
p_G = PWM(Pin(green_pin))  
p_B = PWM(Pin(blue_pin))  
p_R.freq(2000)   
p_G.freq(1999)   
p_B.freq(5000)   
##

colors = [0xFF00, 0x00FF] 
makerobo_pins = (17, 16)  

p_R1 = PWM(Pin(makerobo_pins[0]))  
p_G1 = PWM(Pin(makerobo_pins[1]))  


p_R1.freq(1000) 
p_G1.freq(1000)

def makerobo_pwm_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def makerobo_set_Color(col):   
    R_val = col >> 8
    G_val = col & 0x00FF
   
    R_val = round(makerobo_pwm_map(R_val, 0, 255, 0, 65535))
    G_val = round(makerobo_pwm_map(G_val, 0, 255, 0, 65535))

    p_R1.duty_u16(R_val)    
    p_G1.duty_u16(G_val)     

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
            makerobo_set_Color(0x00FF)
            if (0 == ir_Obstacle.value() and ADC(makerobo_photo).read_u16()>30000):
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
                        while raw_uid[0] == 0x61 and  raw_uid[1] == 0x20 and  raw_uid[2] == 0x34 and  raw_uid[3] == 0x47 and 0 == ir_Obstacle.value():
                            servo_Angle(150)
                            p_R.duty_u16(65535)
                            p_G.duty_u16(0)
                            p_B.duty_u16(0)
                            makerobo_set_Color(0xFF00)
                        p_R.duty_u16(0)
                        p_G.duty_u16(0)
                        p_B.duty_u16(0)
                        servo_Angle(0)
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("HAVE A NICE ",0,9,1)
                        oled.text("DAY!",0,18,1)
                        oled.show()
                    elif raw_uid[0] == 0x70 and  raw_uid[1] == 0xe1 and  raw_uid[2] == 0xdc and  raw_uid[3] == 0x37:
                        print("Card Right! Welcom!")
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("Card Right!",0,9,1)
                        oled.text("Door Open!",0,18,1)
                        oled.show()
                        while raw_uid[0] == 0x70 and  raw_uid[1] == 0xe1 and  raw_uid[2] == 0xdc and  raw_uid[3] == 0x37 and 0 == ir_Obstacle.value():
                            servo_Angle(150)
                            p_R.duty_u16(0)
                            p_G.duty_u16(65535)
                            p_B.duty_u16(0)
                            makerobo_set_Color(0xFF00)
                        p_R.duty_u16(0)
                        p_G.duty_u16(0)
                        p_B.duty_u16(0)
                        servo_Angle(0)
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("HAVE A NICE",0,9,1)
                        oled.text("DAY!",0,18,1)
                        oled.show()
                    elif raw_uid[0] == 0x83 and  raw_uid[1] == 0x14 and  raw_uid[2] == 0x0d and  raw_uid[3] == 0xc5:
                        print("Card Right! Welcom!")
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("Card Right!",0,9,1)
                        oled.text("Door Open!",0,18,1)
                        oled.show()
                        while raw_uid[0] == 0x83 and  raw_uid[1] == 0x14 and  raw_uid[2] == 0x0d and  raw_uid[3] == 0xc5 and 0 == ir_Obstacle.value():
                            servo_Angle(150)
                            p_R.duty_u16(0)
                            p_G.duty_u16(0)
                            p_B.duty_u16(65535)
                            makerobo_set_Color(0xFF00)
                        p_R.duty_u16(0)
                        p_G.duty_u16(0)
                        p_B.duty_u16(0)
                        servo_Angle(0)
                        oled.fill(1)
                        oled.show()
                        oled.fill(0)
                        oled.show()
                        oled.text("HAVE A NICE",0,9,1)
                        oled.text("DAY!",0,18,1)
                        oled.show()
                        
                    else :
                      if stat == rdr.OK:
                            print("Card Error! Try Again!")
                            oled.fill(1)
                            oled.show()
                            oled.fill(0)
                            oled.show()
                            oled.text("Try Again!",0,9,1)
                            oled.text("Door Close!",0,18,1)
                            oled.show()
                            servo_Angle(0)
                            i=0
                            for i in (range(5)):
                                i=i+1
                                p_R.duty_u16(65535)
                                p_G.duty_u16(65535)
                                p_B.duty_u16(65535)
                                sleep(0.1)
                                p_R.duty_u16(0)
                                p_G.duty_u16(0)
                                p_B.duty_u16(0)
                                sleep(0.1)
            else :
            
            
                            servo_Angle(0)
                            p_R.duty_u16(0)
                            p_G.duty_u16(0)
                            p_B.duty_u16(0)
                                
                       
        utime.sleep(0.05)

    except KeyboardInterrupt:
        print("Bye")



if __name__ == '__main__':
    makerobo_setup() 
    oled.fill(1)
    oled.show()
    oled.fill(0)
    oled.show()
    oled.text("HAVE A NICE",0,9,1)
    oled.text("DAY!",0,18,1)
    servo_Angle(0)
    oled.show()
    do_write()

        

