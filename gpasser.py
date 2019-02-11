# This file takes a gcode string and sends it

import sys
import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200)

# Count the number of commands
arguments = len(sys.argv) -1

# Send the commands
position = 1
while(arguments >= position):
    command =  sys.argv[position]
    # Wake up controller
    ser.write("\r\n\r\n")
    time.sleep(2)
    ser.flushInput()
    # Send gcode
    ser.write(sys.argv[position] + "\n")
    grbl_out = ser.readline()
    print(grbl_out.strip())
    position = position + 1

ser.close()
