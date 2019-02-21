#!/usr/bin/env

# This program reads gcode from a file and runs it through the sender
# Current version of this makes test.py obsolete

import serial
import time
import RPi.GPIO as GPIO

z_down = "G0 Z0.8 \n" # Height of top of board
solder_speed = 150 # PWM frequency
extract_time = 0.5 # How long to extract solder
solder_time = 5 # How long to hold iron down

GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)
p = GPIO.PWM(12, solder_speed)


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
ser.write("G0 Z3\n") # Move z up at max feed rate
grbl_out = ser.readline()
print("Move Z axis up: " + grbl_out.strip())
time.sleep(1)

# Declare variable for checking command type
move = 0

# Read inputs from the file
with open("gfile.txt", "r") as f:
  line = f.readline()
  if "G0" in line:
    move = 1
  while line:
    ser.write(line)
    grbl_out = ser.readline()
    time.sleep(1)
    if move:
      ser.write(z_down) # Move z down
      grbl_out = ser.readline()
      p.start(50)
      time.sleep(extract_time)
      p.stop()
      time.sleep(solder_time)
      ser.write("G0 Z3\n") # Move z up
      grbl_out = ser.readline()
      time.sleep(1)
      move = 0
    line = f.readline()
    if "G0" in line:
      move = 1

# Return home and close the serial port
ser.write("G0 X0 Y0\n")
grbl_out = ser.readline()
time.sleep(1)
ser.write("G0 Z0\n")
grbl_out = ser.readline()
time.sleep(5)
ser.close()
