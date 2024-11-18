This version is built on sep 16 2024  
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
4. sudo cp /asn1c/converter-example /usr/local/bin  
we should put the executable file to /usr/local/bin so that we can use system command to call the executable file in convert function
```

- convert function  
we should use the known field and structure to make the covert funtion, like asn1c/asn1_changebyte.c  
```
if we want to offline test the data, we can define the hex data compile the convert code  
gcc try.c -o try
```

- dm_collector_c.cpp and log_packet.cpp  
In the previous version, in the dm_collector_c_receive_log_packet function, after we make sure it is a frame, we include the asn1c/asn1_changebyte.c and call the process_data function.  
But in this version, after the mobileinsight recognized msg_len, logcode, timstamp, and according to the logcode go into the specific switch branch, we call the process_data function in log_packet.cpp.   
We also delete msg_len, logcode and timestamp field in dci_test.asn1 file.  
In order to call and link the asn1c code series and asn1_changebyte.c, we should make the asn1_changebyte.c a dynamic linke library.  
```
1.gcc -fPIC -shared asn1_changebyte.c -o libchangebyte.so  
2.sudo cp /asn1c/libchangebyte.so /usr/local/lib  
3.sudo Idconfig  
4.change the setup.py, add the library_dirs=['../asn1c'], libraries=['changebyte']
```
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

In the following test, we need to test two logcode in the same time.


## 1005 change:  
we redesign the bytechange module and decode module in asn1c  
in asn1c/asn1_cb_dcall.c  
we directly use the uper_decode() function provided by ans1c to do the decode operations  
now the asn1c code series
```
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto dci_test.asn1  
rm converter-example.c(this file just provide main function we need to delete it)
cc -I. -o test *.c
./test
```
in asn1_cb_dcall.c main() we change the byte sequence and use uper_decode to decode, we write the glue code to realize the loop which would be faster compared with the original system command one.  
the call.c is just a test file to test a easy asn1 module and the uper_decode function  
We'll default to using the per to decode.


## 1007 change
we introduce asn1_group directory to save the files before running asn1c compile code  
we export the main.c and executable file test to use  
./test data.dat B16C
Actually we don't need the logcode in command but we still keep it for future

## 1022 change
We add the S_D_V_plugin directory as the plugin to the mobileinsight-core repository  

## 1118 change
We add the S_D_V_phone directory to save the decode.c diag_revealer.c generate_diag_cfg.c which could be used in generat exectuable program in dell /home/ty/Desktop/S_D_V_apk/Ty_apk/S_D_V_diagrevealer  

## workflow now
Now after we finish the asn1 and cb_dcall design, we use this repository to update and test in dell pc  
Each time if we want to update diag_revealer decode generate_diag_cfg, we change it in S_D_V_phone dir and copy it to the dell /home/ty/Desktop/S_D_V_apk/Ty_apk/S_D_V_diagrevealer and test  
If we need to change the code in ans1_group and compile it into executable program by vagrant, we need to use the asn1_group to replace the asn1_group in dell /home/ty/Desktop/S_D_V_apk/Ty_apk/S_D_V_diagrevealer, and use asn1 code seriese to compile it and rm converter, and then use the vbox_change_code.sh which locate inside the vagrant to make the exectable program and then the diag_revealer will show up in /home/ty/Desktop/S_D_V_apk/Ty_apk/S_D_V_diagrevealer, then in thie dir we can change the exectuable name, we ./push_diag_revealer.sh <day> <try_number> <exeutable_name> to put it into phone