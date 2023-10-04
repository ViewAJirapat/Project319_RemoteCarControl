#!/usr/bin/env python
import odroid_wiringpi as wpi
import time
import sys
from time import sleep
import urllib
import requests
import serial
     
serial = wpi.serialOpen('/dev/ttyS1', 115200)
wpi.wiringPiSetup()

baseURL = 'https://api.thingspeak.com/update?api_key=FIK97XTCL1AAKTQ8&field1=0'

     
while True:
 
    output_str = ''
    while wpi.serialDataAvail(serial):
        output_str += chr(wpi.serialGetchar(serial))
    f=urllib.request.urlopen(baseURL+str(output_str))
    f.close()
    #print(output_str)
     
wpi.serialClose(serial)
