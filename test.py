# -*- coding: utf-8 -*-
"""
Serial Binary 6 byte sender
"""
import serial
import time
#initiate communication (make sure to press reset on the arduino before starting):
ser = serial.Serial('/dev/ttyACM0',115200, timeout = 1)
time.sleep(0.5)
ser.write('S'.encode())
if ser.read(1) == 'S'.encode():
    print('Communication Started\n')

    file = open('step48.txt')
    while 1:
        line = file.readline()
        if not line:
            break
        list = line.rstrip().split(',') # rstrip removes any newline symbol at the end
        #   print(list)

        # now merge every 8 elements  into 1 for each of the 6 bytes aka [0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1... 6x] -> [01010101 01010101 ... 6x]
        for e in range(0,6):
            list[0+e:8+e] = [''.join(list[0+e:8+e])]
        print(list)
        # variable for the 6 bytes to send:
        packet = bytearray()
        # variable just for console printing:
        strpacket = []
        # convert the byte strings into integers, and add them to packet so that they become single bytes
        for e in range(0,6):
            anInteger = int(list[e],2)
            strpacket.append(anInteger)
            packet.append(anInteger)
        print('Python sent:')
        print(strpacket)
        # Send the 6 bytes:
        ser.write(packet)
<<<<<<< HEAD
        #time.sleep(0.1)
        # Print mirrored data from arduino:
        print('Arduino Replies:')
        print(ser.readline())
    
=======
        if counter == 100:
            counter = 0
            print('Python sent:')
            print(strpacket)
            #time.sleep(0.1)
            # Print mirrored data from arduino:
            print('Arduino Replies:')
            print(ser.readline())
>>>>>>> removed trailing whitespaces
    file.close
else:
    print('Handshake failed')
print('Finish')

