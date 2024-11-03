import binascii
import os
import optparse
import serial
import sys
import timeit

from . import dm_collector_c
from .dm_endec import *


def run():
    phy_ser_name = "/dev/ttyUSB0"
    phy_baudrate = 9600
    print(("PHY COM: %s", phy_ser_name))
    print(("PHY BAUD RATE: %d", phy_baudrate))
    
    _type_names=["LTE_MAC_DL_Transport_Block"]
    
    
    try:
        phy_ser = serial.Serial(phy_ser_name,
                baudrate=phy_baudrate,
                timeout=None, rtscts=True, dsrdtr=True)     
        
        print("disable logs")
        dm_collector_c.disable_logs(phy_ser)
        
        print("enable logs")
        dm_collector_c.enable_logs(phy_ser, _type_names)

        
        while True:
            s = phy_ser.read(64)
            # feed binary into buffer
            dm_collector_c.feed_binary(s)
            # receive_log_packet
            decoded = dm_collector_c.receive_log_packet(0, True, )
            
            if decoded:
                try:
                    # packet = DMLogPacket(decoded)
                    if not decoded[0]:
                        continue
                    packet = DMLogPacket(decoded[0])
                    type_id = packet.get_type_id()
                except FormatError as e:
                    # skip this packet
                    print(("FormatError: ", e))
            
        
    except (KeyboardInterrupt, RuntimeError, Exception) as e:
        sys.exit(e)
        


if __name__ == "__main__":
    run()