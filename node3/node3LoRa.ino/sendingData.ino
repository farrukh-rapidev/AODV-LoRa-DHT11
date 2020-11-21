void sendingDataQ()
{
  String newRoute = "";
  
  strcpy(dataKirim, "Q"); //RREQ code
  strcat(dataKirim, ","); //Separator
  sprintf(x,"%d",ID);
  strcat(dataKirim, x);  //ID sender
  strcat(dataKirim, ",");

  newRoute = valSplit[2];
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);  //ID destination
  strcat(dataKirim, ",");

  newRoute = valSplit[3];
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);  //message
  strcat(dataKirim, ",");

  newRoute = valSplit[1] + ">" + String(ID);
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);   //route yg tersedia 
  strcat(dataKirim, ",");

  Serial.println(dataKirim);
  Serial.println("-----------");
  
  int state = radio.transmit((byte *)&dataKirim);      // add payload
  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("sending data Q success!"));

    // print measured data rate
    Serial.print(F("Datarate:\t"));
    Serial.print(radio.getDataRate());
    Serial.println(F(" bps"));

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
void sendingDataP(char text[])// sending RREP Node Selanjutnya
{
  String newRoute = "";
  
  strcpy(dataKirim, text); //RREP code
  strcat(dataKirim, ","); //Separator
  sprintf(x,"%d",ID);
  strcat(dataKirim, x);  //ID sender
  strcat(dataKirim, ",");
  
  newRoute = IdNextNodeRREP;//ambil node selanjutnya
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);  //ID sender selanjutnya
  strcat(dataKirim, ",");

  if (text== "Q"||text== "P")
  {
    newRoute = valSplit[3];
    n = newRoute.length() + 1;
    x[n];
    newRoute.toCharArray(x, n);
  }else
  {
    newRoute = dataDHT;
    n = newRoute.length() + 1;
    x[n];
    newRoute.toCharArray(x, n);
  }
  
  strcat(dataKirim, x);  //message
  strcat(dataKirim, ",");

  newRoute = valSplit[4];
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);   //route yg tersedia 
  strcat(dataKirim, ",");

  Serial.println("teruskan : ");
  Serial.println(dataKirim);

  int state = radio.transmit((byte *)&dataKirim);      // add payload
  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("sending data REPP success!"));

    // print measured data rate
    Serial.print(F("Datarate: "));
    Serial.print(radio.getDataRate());
    Serial.println(F(" bps"));
  }
}
void sendingDataLastP(char text[])// sending RREP Data Terakhir
{
  String newRoute = "";
  
  strcpy(dataKirim, text); //RREP code
  strcat(dataKirim, ","); //Separator
  sprintf(x,"%d",ID);
  strcat(dataKirim, x);  //ID sender
  strcat(dataKirim, ",");
  
  newRoute = valSplitNode[banyakNodeYgDiLalui];//ambil node terakhir
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);  //ID sender sebelumnya
  strcat(dataKirim, ",");

  if (text== "Q"||text== "P")
  {
    newRoute = valSplit[3];
    n = newRoute.length() + 1;
    x[n];
    newRoute.toCharArray(x, n);
  }else
  {
    newRoute = dataDHT;
    n = newRoute.length() + 1;
    x[n];
    newRoute.toCharArray(x, n);
  }
  
  strcat(dataKirim, x);  //message
  strcat(dataKirim, ",");

  newRoute = valSplit[4] + ">" + String(ID);
  n = newRoute.length() + 1;
  x[n];
  newRoute.toCharArray(x, n);
  
  strcat(dataKirim, x);   //route yg tersedia 
  strcat(dataKirim, ",");

  radio.transmit((byte *)&dataKirim);      // add payload
  if(text == "A")
  {
    reset();
  }
}
