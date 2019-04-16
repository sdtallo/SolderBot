#!/usr/bin/env python

# Travis Riddle
# Trine University Senior Design 2019
# This program reads gcode from a file and runs it through the sender

import sys
import serial
import time
import atexit
from shutil import copyfile
import RPi.GPIO as GPIO

print("Program starting")

# Variable to keep track of number of commands completed
j = 0

# Copy commands to a temporary file
copyfile("/home/pi/solderbot/gCodeLoc.txt", "/home/pi/solderbot/gTemp.txt")

# Open the serial port
ser = serial.Serial('/dev/ttyUSB0', 115200)

# Set up GPIO mode
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

# Set up emergency interrupt
GPIO.setup(22, GPIO.IN, pull_up_down = GPIO.PUD_UP)
def emergency(channel):
    # Hold machine in current position
    ser.write("!\n")
    print("Emergency stop pressed")
    ser.flushInput()
    time.sleep(3)
    # Record current position in position.txt
    ser.write("?\n")
    grbl_out = ser.readline()
    e = open("/home/pi/solderbot/position.txt", "w")
    e.write(grbl_out)
    e.close()
    # Delete completed commands
    infile = open("/home/pi/solderbot/gTemp.txt", "r").readlines()
    with open("/home/pi/solderbot/gCodeLoc.txt", "w") as ufile:
        for index, line in enumerate(infile):
            if index >= j:
                ufile.write(line)
    ufile.close()
    # Close serial port and clean up GPIO
    #ser.close()
    GPIO.cleanup()
    # Stall program
    while True:
        time.sleep(1)

# Set up exit protocol
def exit_handler():
    ser.write("!\n")
    print("Job cancelled")
    time.sleep(0.5)
    ser.write("\030")
    time.sleep(0.5)
    ser.write("~\n")
    time.sleep(0.5)
    ser.write("G0 Z1")
    grbl_out = ser.readline()
    print("Move Z up")
    time.sleep(1)
    ser.write("G0 X0 Y0")
    grbl_out = ser.readline()
    print("Returning home")
    time.sleep(1)
    ser.write("G0 Z0")
    grbl_out = ser.readline()
    print("Moving down")
    time.sleep(1)
    f1 = open("/home/pi/solderbot/position.txt", "w")
    f1.write("<,:,:0,0,0>")
    f1.close()
    #ser.close()
    GPIO.cleanup()
    print("Finished")

atexit.register(exit_handler)

# Set up PWM with 50 Hz frequency
GPIO.setup(12, GPIO.OUT)
p = GPIO.PWM(12, 50)

# Set up GPIO
GPIO.setup(16, GPIO.OUT)
GPIO.output(16, GPIO.HIGH)

# Get location from last run
i = open("/home/pi/solderbot/position.txt", "r")
trash1 = i.readline()
trash2, trash3,  s = trash1.split(":", 2) 
x, y, tempz  = s.split(",", 2)
z = tempz.replace(">", "")
if "-" in x:
    x = x.replace("-", "")
if "-" in y:
    y = y.replace("-", "")
if "-" in z:
    z = z.replace("-", "")
print("X value: " + x)
print("Y value: " + y)
print("Z value: " + z)
move_home = "G0 X-"+x+" Y-"+y+" Z-"+z+"\n"

# Wake up the controller  
ser.write("\r\n\r\n")
time.sleep(2)
ser.flushInput()
# Unhold
ser.write("~\n")
grbl_out = ser.readline()
time.sleep(1)
# Set units to inches
ser.write("G20\n")
grbl_out = ser.readline()
print("Set units to inches: " + grbl_out.strip())
time.sleep(1)
# Set temporary home position
ser.write("G10 P0 L20 X0 Y0 Z0\n") 
grbl_out = ser.readline()
print("Set home position: " + grbl_out.strip())
time.sleep(1)
# Move z up
ser.write("G0 Z1\n")
grbl_out = ser.readline()
print("Move Z axis up: " + grbl_out.strip())
time.sleep(1)
# Return to actual home
ser.write(move_home)
grbl_out = ser.readline()
print("Returning home: " + grbl_out.strip())
time.sleep(1)
# Set actual home position
ser.write("G10 P0 L20 X0 Y0 Z0\n")
grbl_out = ser.readline()
print("Setting new home position: " + grbl_out.strip())
time.sleep(1)
# Move z up
ser.write("G0 Z1\n")
grbl_out = ser.readline()
print("Move Z axis up: " + grbl_out.strip())
time.sleep(1)

# Turn on interrupt
GPIO.add_event_detect(22, GPIO.FALLING, callback = emergency, bouncetime = 100)

# Wait for soldering iron to heat up
#time.sleep(300)

# Declare variable for checking command type
solder = 0

# Initialize PWM to counter bug
p.start(50)
time.sleep(0.01)
p.stop()

# Read inputs from the file
with open("/home/pi/solderbot/gCodeLoc.txt", "r") as f:
    line = f.readline()
    if "Z" in line:
        solder = 1
    while line:
        ser.write(line)
        grbl_out = ser.readline()
        print("Moving\n")
        time.sleep(1)
        # Wait until stopped to continue
        ser.write("?\n")
        grbl_out = ser.readline()
        while "Idle" not in grbl_out:
            time.sleep(0.5)
            ser.write("?\n")
            grbl_out = ser.readline()
        if solder:
            print("Extracting\n")
            p.start(50)
            #temp = raw_input("Press enter to stop solder\n")
            time.sleep(0.15)
            p.stop()
            print("Soldering\n")
            #temp = raw_input("Press enter to continue\n")
            time.sleep(1)
            ser.write("G0 Z1\n") # Move z up
            grbl_out = ser.readline()
            print("Lifting\n")
            #temp = raw_input("Press enter to continue\n")
            time.sleep(3)
            solder = 0
        #else:
        #    time.sleep(5)
        j = j + 1
        line = f.readline()
        if "Z" in line:
            solder = 1

# Return home and close the serial port
#GPIO.output(18, GPIO.HIGH)
ser.write("G0 X0 Y0\n")
grbl_out = ser.readline()
time.sleep(1)
ser.write("G0 Z0\n")
grbl_out = ser.readline()
ser.flushInput()
ser.write("?\n")
grbl_out = ser.readline()
while "Idle" not in grbl_out:
    time.sleep(0.5)
    ser.write("?\n")
    grbl_out = ser.readline()
fi = open("/home/pi/solderbot/position.txt", "w")
fi.write(grbl_out)
fi.close()
ser.close()
GPIO.remove_event_detect(22)
GPIO.cleanup()
print("Job completed")
sys.exit()

