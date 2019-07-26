import serial 
with serial.Serial('/dev/ttyACM0', 115200) as s:
  while(1):
      x = s.read(1000)
      print(x)


