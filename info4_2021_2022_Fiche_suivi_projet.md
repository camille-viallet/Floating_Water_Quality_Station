# Project Tracking Sheet.
## 28 & 29 March 2022 :
- Ayman & Emeric: Progress on the report
- Camille : Testing the sensors

## 21 & 22 March 2022 :
Using the turbidity and pH sensor and sending the data to Lora. 
*TODO:*
- Perform a calibration with the sensors to ensure that the values produced are accurate.

## 15 March 2022:
Use of the turbidity sensor:
- Reading an analogue value with the riot ADC module on the Lora E5 board.
- Transformation of the raw values into voltage values.
- Test on the functioning of the sensor

*TODO :*
- Finding the true turbidity values from the equation of the line

*Difficulties encountered/questions :*
 - Doubt about the actual presence of the 3.3V on the board.
- Questions about the analog reading of other sensors (there are only two pins allowing analog reading)

## 14 March 2022:
- Problem with the use of the temperature sensor solved (due to a bad initialization of the pin)
- Regular sending of temperature data to Mydevices.com via Cayenne (using Chirpstack and TTN)
- Started on a code with the turbidity sensor

## 8 March 2022 :
Continuation of the previous day's work. Difficulty in getting the temperature sensor to work, problem areas:
- Wrong connection?
- Bad initialization of the pin?
- Incompatible Lora E5 card?

## 7 March 2022:
- Finalisation of the code to send Cayenne packets via LoraWan every 30 seconds: working code.
- Data visualization on myDevices.com: https://cayenne.mydevices.com/cayenne/dashboard/lora/6b797720-9e1f-11ec-8c44-371df593ba58
- Start of the code to read the temperature from the sensor. 

## 01 March 2022
- Created C code to send messages in Lora using Cayenne from the RIOT tutorials provided. Testing has not yet been done. 
- Reading documentation about the sensors and how do we need to use them in order to make them work.

## 28 February 2022:
Joint work:
- Sending data in Lora from the code of a given tutorial. The code allows us to write a message, and we manage to have it received by a nearby LoRa antenna, and then retransmitted to TTN. When we log into our account, we are then able to see the packets that have passed from the card to TTN via the antenna, and the various data contained in the packet. The aim now is to test this with code more suited to our project, to see if we are able to retrieve continuous data.
- Work planning (One person working on the sensor code, one on creating code that sends LoRa packets continuously to TTN, and one on using ThingsBoard)
- Search for documentation on sensors
- Mid-term defense

## 14 February 2022:
Joint work:
- Finalisation of the installation of the various elements.
- Realization of various tutorials on SeedStudio:
    - LoraWAN communication with RIOT
- Familiarisation with the different sensor documentation.
- Project follow-up meeting 

## February 07, 2022 :
Joint work :
- RIOT installation
- Configuration of Lora cards with STM Discovery: https://wiki.seeedstudio.com/LoRa_E5_Dev_Board/
- Integration of devices on TTN and Campus IOT (**exchange DevUIs between CampusIOT, Helium and TTN**)
- Project follow-up meeting with teachers

## 31 January 2022:
Joint work :
- Meeting with Mr. PALIX and Mr. DONSEZ to clarify different points of the specifications and available technologies.
- Analysis of the existing system.

Ayhman : 
- RIOT OS tutorial

Emeric / Camille:
- Lora card tutorial

## 24 January 2022 :

Common work :
- Recovery of the material at the FabLab (3 LoRa E5 cards, turbidity sensor, 3 temperature sensors, 3 Grove shield, a waterproof box...)
- Soldering of the LoRa E5 boards 
- Study of the documentation of the different materials received and analysis of the existing (by studying the similar projects provided)

## January 17, 2022 :

Common work: Follow up of the presentation course on LoRa and LoRaWan in order to get details on their use.



 
