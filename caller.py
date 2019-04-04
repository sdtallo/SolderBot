#!/usr/bin/env python

# This program reads gcode from a file and runs it through the sender
# Current version of this makes test.py obsolete

import serial
import time
import RPi.GPIO as GPIO

print("Program starting\n")

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)
GPIO.setup(3, GPIO.OUT)
GPIO.output(3, GPIO.HIGH)
p = GPIO.PWM(12, 150) # Set PWM frequency
p.start(0)
time.sleep(0.01)
p.stop()


# Open the serial port
ser = serial.Serial('/dev/ttyUSB0', 115200)

# Set up the controller  
ser.write("\r\n\r\n")
time.sleep(2)
ser.flushInput()
ser.write("G20\n") # Set units to inches
grbl_out = ser.readline()
print("Set units to inches: " + grbl_out.strip())
time.sleep(1)
ser.write("G10 P0 L20 X0 Y0 Z0\n") # Set home position
grbl_out = ser.readline()
print("Set home position: " + grbl_out.strip())
time.sleep(1)
ser.write("G0 Z1\n") # Move z up at max feed rate
grbl_out = ser.readline()
print("Move Z axis up: " + grbl_out.strip())
time.sleep(1)

# Declare variable for checking command type
solder = 0

# Read inputs from the file
with open("gCodeLoc.txt", "r") as f:
    line = f.readline()
    if "Z" in line:
        solder = 1
    while line:
        ser.write(line)
        grbl_out = ser.readline()
        print("Moving")
        ser.write("?\n")
        grbl_out = ser.readline()
        while "Idle" not in grbl_out:
            time.sleep(0.5)
            ser.write("?\n")
            grbl_out = ser.readline()
        if solder:
            print("Extracting")
            p.start(50)
            #temp = raw_input("Press enter to stop solder\n")
            time.sleep(1)
            p.stop()
            print("Soldering")
            #temp = raw_input("Press enter to continue\n")
            time.sleep(1)
            ser.write("G0 Z1\n") # Move z up
            grbl_out = ser.readline()
            print("Lifting")
            #temp = raw_input("Press enter to continue\n")
            #time.sleep(1)
            solder = 0
        #else:
        #    time.sleep(5)
        line = f.readline()
        if "Z" in line:
            solder = 1

# Return home and close the serial port
ser.write("G0 X0 Y0\n")
grbl_out = ser.readline()
time.sleep(1)
ser.write("G0 Z0\n")
grbl_out = ser.readline()
time.sleep(5)
ser.close()
