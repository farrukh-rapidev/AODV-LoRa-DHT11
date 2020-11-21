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
1. NSS => D10
2. MOSI	=> D11
3. MISO	=> D12
3. SLCK	=> D13
4. DI00	=> D2
5. DI01	=> D3
6. VCC => 3.3 V
7. GND => GND

Node 2:
![ArduinoUno_i2C_SX1278 DHT POWER SUPPLY](https://user-images.githubusercontent.com/40090896/99866987-69a8a880-2be8-11eb-8344-12b7581f3305.png)

LoRa SX1278 + Arduino Uno:
1. NSS => D10
2. MOSI	=> D11
3. MISO	=> D12
4. SLCK	=> D13
5. DI00	=> D2
6. DI01	=> D3
7. VCC => 3.3 V
8. GND => GND

DHT+ Arduino Uno:
1. Out => A0
2. VCC(+) => 5 V
3. GND(-) => GND
