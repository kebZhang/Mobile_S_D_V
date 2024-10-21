import binascii
import os
import optparse
import serial
import sys
import timeit


def run():
    phy_ser_name="/dev/USB0"
    phy_baudrate=9600
    print(("PHY COM: %s", phy_ser_name))
    print(("PHY BAUD RATE: %d", phy_baudrate))
    
    phy_ser = serial.Serial(phy_ser_name,
                        baudrate=phy_baudrate,
                        timeout=None, rtscts=True, dsrdtr=True)
    
    