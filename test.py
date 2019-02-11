# Program to send test data over serial

import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200)

pins = input("How many pins would you like to solder? ")
xCoords = []
yCoords = []
zCoords = []

# Record pin locations
for i in range (pins):
        temp = input("What is the x location of pin " + str(i) + "? ")
        xCoords.append(temp * 0.1)
        temp = input("What is the y location of pin " + str(i) + "? ")
        yCoords.append(temp * 0.1)
        
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

for j in range (pins):
        ser.write("G0 X" + str(xCoords[j]) + " Y" + str(yCoords[j])+"\n") # Move to x and y coordinate 
        grbl_out = ser.readline()
        print("Move to pin: " + grbl_out.strip())
        time.sleep(3)
        ser.write("G0 Z0\n") # Move z down at max feed rate
        grbl_out = ser.readline()
        print("Move z down: " + grbl_out.strip())
        time.sleep(3)
        ser.write("G0 Z3\n") # Move z up at max feed rate
        grbl_out = ser.readline()
        print("Move z up: " + grbl_out.strip())
        time.sleep(3)

raw_input("Press <Enter> to end")
ser.write("G0 X0 Y0 Z0\n")
grbl_out = ser.readline()
print("Return home: " + grbl_out.strip())
time.sleep(5)
ser.close()

