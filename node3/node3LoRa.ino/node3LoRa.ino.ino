#include <SPI.h>
#include <RadioLib.h>
#include <stdlib.h>
#include "DHT.h"

#define ID  3
#define DHTPIN A0
#define DHTTYPE DHT11

// SX1278 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 9
// DIO1 pin:  3
SX1278 radio = new Module(10, 2, 9, 3);
DHT dht(DHTPIN, DHTTYPE);

char data[32];
String valSplit[6];
String valSplitNode[10];
char dataKirim[32];
char dataDHT[32];
char x[32];
int n;
boolean flag=0;
int banyakNodeYgDiLalui;
String IdNextNodeRREP;
int longRute = 0;
int samePackage = 0;
const long frequency = 915E6;  // LoRa Frequency
const int csPin = 10;          // LoRa radio chip select
const int resetPin = 9;        // LoRa radio reset
const int irqPin = 2;          // change for your board; must be a hardware interrupt pin

//format
// RREQ,        ID_Sender,  ID_Destination, Message,  Route
// valSplit[0], [1],        [2],            [3],      [4]
void(*reset) (void) = 0;
void setup(){
  Serial.begin(115200);
  dht.begin();

  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println("---LoRa AODV---"); 
    Serial.println("---ini node 3---"); 
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
      double floatVal=dht.readTemperature();
      char charVal[4];               //temporarily holds data from vals 
      String stringVal = "";         //data on buff is copied to this string
      dtostrf(floatVal, 4, 1, charVal);
      for(int i=0;i<sizeof(charVal);i++)
      {
  //      Serial.print(charVal[i]);
      }
      for(int i=0;i<sizeof(charVal);i++)
      {
        stringVal+=charVal[i];
      }
      strcpy(dataDHT, "TEMP: ");
      strcat(dataDHT, charVal);
      strcat(dataDHT, " 'C");

      Serial.println(dataDHT);
}

void loop(){
      receiveData();
}
