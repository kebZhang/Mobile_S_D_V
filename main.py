import binascii
import os
import optparse
import serial
import sys
import timeit

from mobile_insight.monitor.dm_collector import dm_collector_c
from mobile_insight.monitor.dm_collector.dm_endec import *


def run(phy_ser_name, phy_baudrate):
    print(("PHY COM: %s" % phy_ser_name))
    print(("PHY BAUD RATE: %s" % phy_baudrate))
    
    _type_names = ["LTE_MAC_DL_Transport_Block"]
    
    try:
        phy_ser = serial.Serial(
            phy_ser_name,
            baudrate=int(phy_baudrate),  # 确保波特率为整数
            timeout=None,
            rtscts=True,
            dsrdtr=True
        )
        
        print("disable logs")
        dm_collector_c.disable_logs(phy_ser)
        
        print("enable logs")
        dm_collector_c.enable_logs(phy_ser, _type_names)

        while True:
            s = phy_ser.read(64)
            # feed binary into buffer
            dm_collector_c.feed_binary(s)
            # receive_log_packet
            decoded = dm_collector_c.receive_log_packet(0, True)
            
            if decoded:
                try:
                    if not decoded[0]:
                        continue
                    packet = DMLogPacket(decoded[0])
                    type_id = packet.get_type_id()
                except FormatError as e:
                    print(("FormatError: ", e))
    
    except (KeyboardInterrupt, RuntimeError, Exception) as e:
        sys.exit(e)


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 main.py <serial_port> <baud_rate>")
        sys.exit(1)

    phy_ser_name = sys.argv[1]
    phy_baudrate = sys.argv[2]
    
    run(phy_ser_name, phy_baudrate)
