#!/usr/bin/env

import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)
GPIO.output(16, GPIO.HIGH)
p = GPIO.PWM(12, 150)

p.start(0)
time.sleep(0.01)
p.stop()

direction = input("Enter 1 for forward\nEnter 0 for backward\n")
if(direction):
    GPIO.output(16, GPIO.HIGH)
else:
    GPIO.output(16, GPIO.LOW)

p.start(50)
temp = raw_input("Press enter to stop")
p.stop()
