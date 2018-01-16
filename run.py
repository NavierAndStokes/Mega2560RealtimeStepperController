# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import serial
ser = serial.Serial('/dev/ttyACM2',115200)



file = open('step.csv')
while 1:
   line = file.readline()
   print(line)
   if not line:
        break
   ser.write(line.encode())
   print(ser.read(48))
  
file.close
print('Finish')
