# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import serial

file = open('nine.bin', 'rb')
for x in range(0, 100):
   bytelist = []
   for y in range(0, 6):
      theBits = file.read(8)
      if not theBits:
         break
      aByte = ord(theBits[0]) + ord(theBits[1])*2 +  ord(theBits[2])*4 + ord(theBits[3])*8 + ord(theBits[4])*16 + ord(theBits[5])*32 + ord(theBits[6])*64 + ord(theBits[7])*128
      bytelist.append('{0:08b}'.format(aByte))
   print bytelist

file.close
print('Finish')
