# Performance Count

Collect hardware count and temperature when running benchmark

## Very simple instruction of installation:  

### Prerequisites:
System：Ubuntu 20.04.5 LTS    
cpu:i5-6500
third-party tools:    
    (1)cpupower, to control the running frequency  
    (2)lm-sensors, to read temperature sensor results  
hardware: The CPU should have built-in temperature sensors  


### Installation:
#### change the CMakeLists.txt in the top directory, if necessary
 by default, the two feature, reading hardware temperature sensors and estimating 
temperature based on performance counters, are both enabled. The user can disable 
and enable them by changing the line 3 and 4 of the CMakeLists.txt in the top 
directory. For example, to disable reading hardware sensors, change line 3 to:
 set(HARD_TEMPERATURE_SENSOR_ENABLE "OFF")
#### pre-complile PAPI, if you want to use the software temperature estimator
 cd third_party_lib/papi-5.5.1/src
 
 ./configure
 
 make
 
 sudo make install-all
 
 cd ../../../
#### make and go to the program build directory
 mkdir build
 
 cd build
#### cmake
 cmake ..
#### compile the program 
 make

### run the program:
#### first change the cpu frquency governor as userspace, if you want to control the cpu frequency
a. sudo cpupower -c all frequency-set -g userspace 
#### set FREQUENCY that your device support
b. sudo cpupower -c all frequency-set -f FREQUENCY
#### then go to the program directory
c. cd ../dataset
#### then make
d. make
#### run the program and collecting data
e. sudo python test.py


### notice
A file saving performance counts and related hardware temperatures will be generated in this directory one hour later

You can modify the running time of the program and the frequency of data collection in Examplebenchmark.xml,test.py and 
preset_native_test.c



    
