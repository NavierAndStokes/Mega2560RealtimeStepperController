# Mega2560RealtimeStepperController
This is an Arduino / Python project that allows the user to control up to 22 stepper motors simultaneously from python

This was designed to work on an arduino Mega2560 since this uses direct port manipulation, but it wouldn't be difficult to port it to other microcontrollers
maximum dudy cycle is around 3khz

Usage is pretty straightforward, 
- Create a step48.txt file with your csv data (see existing file)
- The first 3 bytes correspond to the direction and the latter 3 to the pulses to be sent
