# AODV-LoRa-DHT11
AODV routing assuming the shortest distance using 3 Arduino UNOs for sending temperature from DHT11

hardware :
1. Arduino UNO
2. LoRa RA-02 / SX1278
3. Power supply
4. Cable jumper

Schematics:
Node 1:
![Arduino_Uno_i2C_LCD SX1278 SERVER](https://user-images.githubusercontent.com/40090896/99866989-6ad9d580-2be8-11eb-8eb9-9f13fae98bff.png)

LoRa SX1278 + Arduino Uno:
NSS	  D10
MOSI	D11
MISO	D12
SLCK	D13
DI00	D2
DI01	D3
VCC	  3.3 V
GND	  GND

Node 2:
![ArduinoUno_i2C_SX1278 DHT POWER SUPPLY](https://user-images.githubusercontent.com/40090896/99866987-69a8a880-2be8-11eb-8344-12b7581f3305.png)

LoRa SX1278 + Arduino Uno:
NSS	  D10
MOSI	D11
MISO	D12
SLCK	D13
DI00	D2
DI01	D3
VCC	  3.3 V
GND	  GND

DHT+ Arduino Uno:
Out       A0
VCC(+)	  5 V
GND(-)	  GND
