# This program reads gcode from a file and runs it through the sender

import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200)

# Set up controller  
ser.write("\r\n\r\n")
time.sleep(2)
ser.flushInput()
ser.write("G20\n") # Set units to inches
grbl_out = ser.readline()
print("Set units to inches: " + grbl_out.strip())
time.sleep(1)
ser.write("G10 P0 L20 X0 Y0 Z0\n")
grbl_out = ser.readline()
print("Set home position: " + grbl_out.strip())
time.sleep(1)
#ser.write("G90\n") # Set absolute movement
#grbl_out = ser.readline()
#print("Set absolute movement: " + grbl_out.strip())
#time.sleep(1)
#ser.write("G1 F6") # Set feed rate to 6 in/min
#time.sleep(1)
ser.write("G0 Z3\n") # Move z up at max feed rate
grbl_out = ser.readline()
print("Move Z axis up: " + grbl_out.strip())
time.sleep(1)

# Read inputs from file
with open("gfile.txt", r) as f
  ser.write(f.readlines())
  grbl_out = ser.readline()
  time.sleep(3)

# Return home and end
ser.write("G0 X0 Y0 Z0\n")
grbl_out = ser.readline()
time.sleep(5)
ser.close()
