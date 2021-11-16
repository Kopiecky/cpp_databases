import serial
from time import sleep

ser = serial.Serial('/dev/ttyUSB1', timeout=0.5)
print(ser.name)

packet = bytearray()

packet.append(0x11)
packet.append(0x00)
packet.append(0x00)
packet.append(0x11)

while True:
	ser.write(packet)
	sleep(0.5)
	response = bytearray()

	s = ser.read(4)

#	for i in range(0, 4):
#		response.extend(ser.read(1))
#		sleep(0.5)
#	distance = response[1] << 8
#	distance = distance + response[2]
	print(s)