This directory is a supplementary plug-in for mobileinsight  
After you have completed the installation of mobileinsight-core, you can add our plug-in dynamic linked libarary into the code to include more message_types  
The message types we extra support is showed in asn1_group/readme.md  
## Installation Manual
1. Generating Dynamic Linked Libarary
```
cd asn1_group
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto *.asn1
rm converter-example.c   
rm libhost.so
gcc -fpIC -shared libhost.so *.c -I/your header files directory
sudo cp libhost.so /usr/local/lib
sudo ldconfig
```
2. Replace the consts.h dm_collector_c.cpp, log_packet.cpp, setup.py, in mobileinsight-core with our provided in this directory.
3. Re setup mobileinisght-core 
```
sudo python3 setup.py build_ext inplace
sudo python3 setup.py install
./install_ubuntu.sh
```
4. decide which msg types you wanna open and change the monitor-example.py and run it
5. log file instruction:  
extra message types decode result in xml: decode_result.txt    
former mobileinsight message types decode result: ondemand_decode_result.txt  
debug in dm_collector_c.cpp: switch_logcode.txt  


### Tip:
We still need to do some error handling work incase file not close or sth else.  
We have test this plugin in samsung s22 ultra unrooted and dell ubuntu 20.04  
We have opend B16C and B0C0 at the same time and tested