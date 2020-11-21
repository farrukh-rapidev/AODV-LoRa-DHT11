
void sendingData(char dest[], char text[])
{    
  strcpy(dataKirim, "Q"); //RREQ code
  strcat(dataKirim, ","); //Separator
  sprintf(x,"%d",ID);
  strcat(dataKirim, x);  //ID sender
  strcat(dataKirim, ",");
  strcat(dataKirim, dest);  //ID destination
  strcat(dataKirim, ",");
  strcat(dataKirim, text);  //message
  strcat(dataKirim, ",");
  sprintf(x,"%d",ID);
  strcat(dataKirim, x);//route masih kosong 
  strcat(dataKirim, ",");

  Serial.println();
  Serial.print("Sending to: ");
  Serial.println(dataKirim);

  int state = radio.transmit((byte *)&dataKirim);      // add payload
  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("sending data success!"));
    // print measured data rate
    Serial.print(F("Datarate: "));
    Serial.print(radio.getDataRate());
    Serial.println(F(" bps"));
    Serial.print(F("RSSI: "));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));
    }
}
void sendingAodv(char dest[], char text[], String route)
{  
  strcpy(dataKirim, "A"); //RREQ code
  strcat(dataKirim, ","); //Separator
  sprintf(x,"%d",ID);
  strcat(dataKirim, x);  //ID sender
  strcat(dataKirim, ",");
  strcat(dataKirim, dest);  //ID destination
  strcat(dataKirim, ",");
  strcat(dataKirim, text);  //message
  strcat(dataKirim, ",");

  String newRoute = "";
  newRoute = route;//ambil jalur routing
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);//route yg akan dilalui
  strcat(dataKirim, ",");

  Serial.println();
  Serial.print("Sending AODV to: ");
  Serial.println(dataKirim);
  
  int state = radio.transmit((byte *)&dataKirim);      // add payload
  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("sending AODV success!"));

    // print measured data rate
    Serial.print(F("Datarate: "));
    Serial.print(radio.getDataRate());
    Serial.println(F(" bps"));
    Serial.print(F("RSSI: "));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));

  } else if (state == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(F("too long!"));

  } else if (state == ERR_TX_TIMEOUT) {
    // timeout occurred while transmitting packet
    Serial.println(F("timeout!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }
}

void aodvSession(char text[], int timeOut)
{
  millis();
  for(int ulang = 0; ulang <= ulangAodvSession; ulang++)
  {
    for(int node = 2; node <= nodeClient; node++)
    {
      flag = false;
      millisNow = millis();
      while((millis()-millisNow) <= timeOut*500)
      {
        if(!flag)
        {
          hasilRouting[node][0];
          //Serial.println(hasilRouting[node][0]);
          parseNodeBefore(hasilRouting[node][0],">");
          //Serial.println(valSplitNode[banyakNodeYgDiLalui]);
          
          String newRoute = "";
          newRoute = valSplitNode[banyakNodeYgDiLalui];
          n = newRoute.length() + 1;
          xx[n];
          newRoute.toCharArray(xx, n);
          
          sendingAodv(xx,text,hasilRouting[node][0]);
          
          receiveData(true);
          
          flag = true;
        }
        receiveData(true);
      }
    }
  }
  
}
