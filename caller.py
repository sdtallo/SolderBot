#!/usr/bin/env

# This program reads gcode from a file and runs it through the sender

import serial
import time
import RPi.GPIO as GPIO

z_down = "G0 Z0.45 \n" # Height of top of board
solder_speed = 150 # PWM frequency
extract_time = 0.5 # How long to extract solder
solder_time = 5 # How long to hold iron down

GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)
p = GPIO.PWM(12, solder_speed)


# Open the serial port
ser = serial.Serial('/dev/ttyUSB0', 115200)
time.sleep(0.1)

# Set up the controller  
ser.write("\r\n\r\n")
time.sleep(2)
ser.flushInput()
# Set units to inches
ser.write("G20\n")
grbl_out = ser.readline()
print("Set units to inches: " + grbl_out.strip())
# Set home position
ser.write("G10 P0 L20 X0 Y0 Z0\n")
grbl_out = ser.readline()
print("Set home position: " + grbl_out.strip())
# Move z up
ser.write("G0 Z2\n")
grbl_out = ser.readline()
print("Move Z axis up: " + grbl_out.strip())

# Let serial buffer catch up
time.sleep(10)

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
    ser.write("?\n") # Get status
    grbl_out = ser.readline()
    # Wait until command has finished
    while "Idle" not in grbl_out:
        time.sleep(0.2)
        ser.write("?\n")
        grbl_out = ser.readline()
        
    if move:
      ser.write(z_down) # Move z down
      grbl_out = ser.readline()
      ser.write("?\n") # Get status
      grbl_out = ser.readline()
      # Wait until command has finished
      while "Idle" not in grbl_out:
        time.sleep(0.2)
        ser.write("?\n")
        grbl_out = ser.readline()
      p.start(50)
      time.sleep(extract_time)
      p.stop()
      time.sleep(solder_time)
      ser.write("G0 Z2\n") # Move z up
      grbl_out = ser.readline()
      ser.write("?\n") # Get status
      grbl_out = ser.readline()
      # Wait until command has finished
      while "Idle" not in grbl_out:
        time.sleep(0.2)
        ser.write("?\n")
        grbl_out = ser.readline()
      move = 0
    line = f.readline()
    if "G0" in line:
      move = 1

# Return home and close the serial port
ser.write("G0 X0 Y0\n")
grbl_out = ser.readline()
ser.write("G0 Z0\n")
grbl_out = ser.readline()
time.sleep(15)
ser.close()
