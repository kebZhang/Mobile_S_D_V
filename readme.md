This version is built on sep 4 2024  
b16c ml1 dci information report is added by using dm_collector_c/ml1_dci_infomation_report.h  
we developed the receive_log_packet_debug in dm_collector_c.cpp, examples/debug.py, Dmcollector_c/dm_collector.py/run_debug func  
we developed this by using mobileinsight protocal and way
we haven't do anything to visualize it  


# asn1c
We could define asn1 of different message type.
But asn1 seems can not deal with big endian and little endian convert process.  
So after we make sure the structure and exact field of specific message type, we could define each part of the message type with asn1, make specific convert function and use different pdu to realize the decode process.  
The documents are: asn1c code series, convert function, dm_collector_c.cpp  

- asn1c code series
```
1.asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto dci_test.asn1  
2. make -f coverter-example.mk  
3. the executable file is converter-example
```

- convert function  
we should use the known field and structure to make the covert funtion, like asn1c/asn1_changebyte.c  
```
if we want to offline test the data, we can define the hex data compile the convert code  
gcc try.c -o try
```

- dm_collector_c.cpp  
<font color="red">  
The following process is used now(deal the whole process include metadataheader), but in the future, I have to recognized the message metadataheader without asn1, and then use the logcode and version to switch into exact process function.
We also need to change the way of calling converter-example     
</font>  
in the dm_collector_c_receive_log_packet function, after we make sure it is a frame, we include the asn1c/asn1_changebyte.c and call the process_data function.  
In order to call and link the asn1c code series and asn1_changebyte.c, we should make the asn1_changebyte.c a dynamic linke library.  \


1.gcc -fPIC -shared asn1_changebyte.c -o libchangebyte.so  
2.sudo cp /asn1c/libchangebyte.so /usr/local/lib  
3.sudo Idconfig  
4.change the setup.py, add the library_dirs=['../asn1c'], libraries=['changebyte']
```
dm_collector_c_module = Extension('mobile_insight.monitor.dm_collector.dm_collector_c',
                                  sources=["dm_collector_c/dm_collector_c.cpp",
                                           "dm_collector_c/export_manager.cpp",
                                           "dm_collector_c/hdlc.cpp",
                                           "dm_collector_c/log_config.cpp",
                                           "dm_collector_c/log_packet.cpp",
                                           "dm_collector_c/utils.cpp", ],
                                  define_macros=[('EXPOSE_INTERNAL_LOGS', 1), ],
                                  library_dirs=['../asn1c'],
                                  libraries=['changebyte'],
                                  )
```
- after we made the process above, we need to complie the whole project
```
1.sudo python3 setup.py build_ext --inplace  
2.sudo python3 setup.py install  
3../install_ubuntu.sh  

```
- run the example function
```
sudo python3 monitor-example.py /dev/ttyUSB0 9600 > /home/ty/Desktop/log/asn1/try1.txt 2>&1
```