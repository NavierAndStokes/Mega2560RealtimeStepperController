# -*- coding: utf-8 -*-
"""
Serial Binary 6 byte sender
"""
import serial
import time
#initiate communication (make sure to press reset on the arduino before starting):
ser = serial.Serial('/dev/ttyACM0',230400, timeout = 1)
time.sleep(0.5)
ser.read()
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
<<<<<<< HEAD
        #time.sleep(0.1)
        # Print mirrored data from arduino:
        print('Arduino Replies:')
        print(ser.readline())
    
=======
        if counter == 100:
=======
        if counter == 200:
>>>>>>> upgraded to 3125Hz, mirror every 200th data point
            counter = 0
            print('Python sent:')
            print(strpacket)
            #time.sleep(0.1)
            # Print mirrored data from arduino:
<<<<<<< HEAD
            print('Arduino Replies:')
            print(ser.readline())
>>>>>>> removed trailing whitespaces
=======
            print('Arduino Replied:')
            response = ser.readline()
            print(response)
            # Get how many items are in the buffer
            inbuffer = int(response.rstrip().split('B'.encode())[1])
            #Since the stepper service is running at 3125Hz, waiting 0.1s should clear at least 312 items in the buffer
            if  inbuffer > 800:
                time.sleep(0.1)
>>>>>>> Added a pause if the buffer was getting full
    file.close
else:
    print('Handshake failed')
print('Finish')

