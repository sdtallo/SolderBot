# Program to send test data over serial

import serial

ser = serial.Serial('/dev/ttyUSB0', 115200)

pins = input("How many pins would you like to solder?")
xCoords = []
yCoords = []
zCoords = []

# Record pin locations
for i in range (pins):
        temp = raw_input("What is the x location of pin " + str(i))
        xCoords.append(temp * 0.1)
        temp = raw_input("What is the y location of pin " + str(i))
        yCoords.append(temp * 0.1)
        
# Set up controller        
ser.write("G20") # Set units to inches
time.sleep(1)
ser.write("G90") # Set absolute movement
time.sleep(1)
ser.write("G1 F6") # Set feed rate to 6 in/min
time.sleep(1)
ser.write("G0 Z3") # Move z up at max feed rate
time.sleep(1)
ser.write("G0 X0 Y0") # Move x and y to home at max feed rate
time.sleep(1)

for j in range (pins):
        ser.write("G1 X" + str(xCoords[j]) + " Y" + str(yCoords[j])) # Move to x and y coordinate at 6 in/min
        time.sleep(3)
        ser.write("G1 Z0") # Move z down at 6 in/min
        time.sleep(3)
        ser.write("G0 Z0") # Move z up at max feed rate
        time.sleep(3)

