import serial
from time import sleep

ser = serial.Serial("/dev/ttyS0", 115200)