boolean validData = true;
String dataSebelumnya;
boolean aodvSession = false;

void receiveData()
{
  byte data[32];
  int state = radio.receive(data, 32);
  if(state == ERR_NONE){                              //!Mirf.isSending() && Mirf.dataReady()

    // packet was successfully received
    Serial.println();
    Serial.println(F("receive success!"));

    // print the data of the packet
    Serial.print(F("Data: "));
    Serial.println(data[32]);
    
    validData = true;
    samePackage = 0;
    longRute = 0;
    
//    radio.receive(data);              // add payload  || getData

//    Serial.print("Data RAW: ");
//    Serial.println(data);
  }
    if(dataSebelumnya != data)
    {
      parseData(data,",");            //pisah data
      parseNodeBefore(valSplit[4],">");//cari node terakhir
      cekDest(ID);
    }
//    else
//    {
//      Serial.println("Data Sama...");
//      Serial.println("ini node 3...");
//      for(int dd=0; dd<=32; dd++)
//      {
//        data[dd] = '\0';
//      }
//      delay(1000);
//    }
    dataSebelumnya = data;
}
void parseData(char text[], String key)
{
  String dataString = String(text);
  int countSplitSecond=0;
  int lastIndexSecond=0;
  for(int j = 0; j < dataString.length(); j++)
  {
    if(dataString.substring(j, j+1) == key)
    {
      valSplit[countSplitSecond] = dataString.substring(lastIndexSecond,j);
      lastIndexSecond = j + 1;
      //Serial.print(countSplitSecond);
      //Serial.print(":");
      //Serial.println(valSplit[countSplitSecond]);
      countSplitSecond++;
    }
  }
}

void cekDest(int myId)
{
  for(int ii=0; ii<=4; ii++)
  {
    if(valSplit[ii] == "")
    {
      validData = false;
    }
  }
  if(validData)
  {
    if(valSplit[2] == String(myId))
    {
      if(valSplit[0] == "P")
      {
        cekPaket(ID);//cek paket apakah sudah pernah di terima?
        if(samePackage != 2)
        {      
          //delay(50);
          putNodeBefore(ID);
          sendingDataP("P");
          Serial.println("Received RREP, and Broadcast RREP");
          Serial.println();
        }
        else
        {
          Serial.println("Paket Sama...");
          Serial.println(); 
        }
      }
      else if(valSplit[0] == "A")
      {
        aodvSession = true;
        Serial.println("Got AODV, Sending AODV Data ");
        putNodeBefore(ID);
        sendingDataP("V");
        //sendingDataP("V");
        Serial.println();
      }
      else
      {
        //delay(50);
        Serial.print("Got RREQ, Sending RREP ");
        Serial.println(valSplitNode[banyakNodeYgDiLalui]);
        sendingDataLastP("P");
        Serial.println();
      }
    }
    else
    {
      //delay(50);
      if(valSplit[0] == "A")
      {
        aodvSession = true;
        Serial.println("Broadcast AODV");
        radio.receive(data, 32);      // add payload || Mirf.send
        
      }
      else if(valSplit[0] == "V")
      {
        Serial.println("AODV ke Coordinator");
      }
      else
      {
        if(valSplit[0] == "Q" && valSplit[2] == "1")
        {
          Serial.println("Error..");
        }
        else
        {
          if(!aodvSession)
          {
            Serial.println("Broadcast...");
            sendingDataQ();
          }
        }
      }
    }
  }
  else
  {
    Serial.println("Data Not Falid");
    Serial.println();
    delay(1000);
  }
}
void cekPaket(int myId)
{
  String id = String(myId);
  for(int rutePaket = 0; rutePaket <= longRute; rutePaket++)
  {
    if(valSplitNode[rutePaket] == id)
    {
      samePackage++;
    }
  }
}
