# Floating Water Quality Station <img align="right" src="https://upload.wikimedia.org/wikipedia/fr/5/5c/Logo_polytech.png" width="300"/>
**Authors :** FAGHLOUMI Ayman - BRETON Emeric - VIALLET Camille                            
**Referent teachers :** DONSEZ Didier - PALIX Nicolas

This project was carried out as part of the Semester 8 projects by 3 computer science students at Polytech Grenoble. 

The aim of this project is to measure different parameters related to water quality. Several sensors are immersed in the water to collect data. The data is then transmitted to the MyDevices solution using LoRaWan technology, allowing the data to be visualised.
The sensor data can be viewed in real time at the following link: : https://cayenne.mydevices.com/shared/622617163916a44bc3006fba/project/6c969f19-84d3-4e0c-a026-6479296ef3f5

## Pre-requisites : 
- In order to use this project it is necessary to have cloned the RIOT OS repository: https://github.com/RIOT-OS/RIOT at the same level as the clone of this repository. 
- A summary of important tutorials and several useful elements to get started and use RIOT, LoraWan is available [here](Help and tutorials.md)


## Sensors used and connection to the board :
The card used is a Lora E5 mini card supplied by Seed Studio : [Card documentation](https://wiki.seeedstudio.com/LoRa_E5_mini/)

### Temperature sensor connection
The temperature is measured with the DS18B20 temperature sensor: [Datasheet](https://files.seeedstudio.com/wiki/One-Wire-Temperature/res/DS18B20-Datasheet.pdf). Documentation on the use of this sensor with RIOT OS is available [here](https://doc.riot-os.org/group__drivers__ds18.html)  


Connection of the DS18 temperature sensor to the LoraE5 board:
- Red wire: 5V
- Black wire: GND
- Yellow wire: D0
- White wire: not used

### Turbidity sensor connection :
The turbidity sensor SKU__SEN0189 used is from DF_Robot : [Datasheet](https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189)  
Connection of the turbidity sensor to the LoraE5 board:
- Red wire: 5V
- Black wire: GND
- Blue : A3

### pH sensor connection
The pH sensor used is the SEN069 from DF_Robot : [Datasheet](https://wiki.dfrobot.com/Analog_pH_Meter_Pro_SKU_SEN0169)  
Connection of the turbidity sensor to the LoraE5 board:
- **Red wire: GND**
- **Black wire: 5V**
- Blue : A4

![Schematic](https://gricad-gitlab.univ-grenoble-alpes.fr/Projets-INFO4/21-22/10/docs/-/raw/main/img/schematic.png)

## Compile the program : 
You need to run the following make command: `make BOARD=lora-e5-dev LORA_DRIVER=sx126x_stm32wl REGION=EU433`    
Then you need to flash the card ( some informations to that are available [here](Help and tutorials.md))

For more information on the functioning of this project you can consult [this report](Floating_Water_Quality_Station_-_Report_.pdf)
