import serial 
import sys
with serial.Serial('/dev/ttyACM0', 115200) as s:
  while(1):
    x = s.readline()
    print(x)


