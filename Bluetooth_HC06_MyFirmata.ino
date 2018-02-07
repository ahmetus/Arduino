// Bluetooth HC06

// Author : ChungYi Fu (Taiwan)  2018-2-8 00:00 

// Command format :  
// Number：  ?cmd  ?cmd=num1  ?cmd=num1,num2
// String ： ?&cmd=str1  ?&cmd=str1,str2 
// String+Number ： ?+cmd=str1,num2   

// ?inputpullup=3
// ?pinmode=3,1
// ?digitalwrite=3,1
// ?analogwrite=3,200
// ?digitalread=3
// ?analogread=3
// ?&message=Hello
// ?&message=Hello,World
// ?+message=Hello,100


#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // Arduino RX:10, TX:11 

void setup()
{
  Serial.begin(9600);
  mySerial.begin(57600);
}

void loop() 
{
  String ReceiveData="", command="";
  long int num1=-1,num2=-1;
  String cmd="",str1="",str2="";
  byte ReceiveState=0,cmdState=1,num1State=0,num2State=0;
  
  if (mySerial.available())
  {
    while (mySerial.available())
    {
      char c=mySerial.read();
      delay(10);
      ReceiveData=ReceiveData+String(c);
      
      if (String(c).indexOf("?")!=-1) ReceiveState=1;
      if (String(c).indexOf(" ")!=-1) ReceiveState=0;
      if ((ReceiveState==1)&&(String(c).indexOf("?")==-1)) 
      {
        command=command+String(c);

        if ((String(c).indexOf("=")!=-1)&&(ReceiveState==1)) cmdState=0;
        if (cmdState==1) cmd=cmd+String(c);

        if ((String(c).indexOf("=")!=-1)&&(ReceiveState==1)) num1State=1;
        if (((String(c).indexOf(",")!=-1)||(String(c).indexOf(" ")!=-1))&&(ReceiveState==1)) num1State=0;
        if ((num1State==1)&&(String(c).indexOf("=")==-1))
        {
          if ((ReceiveData.indexOf("?&")!=-1)||(ReceiveData.indexOf("?+")!=-1))
            str1=str1+String(c);
          else
          {
            if (num1==-1) 
              num1=c-'0'; 
            else
              num1=num1*10+(c-'0'); 
          }
        }
        
        if ((String(c).indexOf(",")!=-1)&&(ReceiveState==1)) num2State=1;
        if ((String(c).indexOf(" ")!=-1)&&(ReceiveState==1)) num2State=0;
        if ((num2State==1)&&(String(c).indexOf(",")==-1))
        {
          if (ReceiveData.indexOf("?&")!=-1)
            str2=str2+String(c);
          else
          {          
            if (num2==-1) 
              num2=c-'0'; 
            else
              num2=num2*10+(c-'0'); 
          }
        } 
      }
    }  
    Serial.println(ReceiveData);
  }

  if (ReceiveData!="")
  {
    Serial.println("");
    Serial.println("command: "+command);
    Serial.println("cmd: "+cmd);
    Serial.println("num1= "+String(num1)+" ,num2= "+String(num2));
    Serial.println("str1= "+String(str1)+" ,str2= "+String(str2));
  }

  while (mySerial.available())
  {
    mySerial.read();
  }
  
  if (cmd=="your command")
    {
      // you can do anything
      //SendData("Hello World");
    }
  else if (cmd=="inputpullup")
    {
      pinMode(num1, INPUT_PULLUP);
      SendData(command);
    }  
  else if (cmd=="pinmode")
    {
      pinMode(num1, num2);
      SendData(command);
    }        
 else if (cmd=="digitalwrite")
    {
      digitalWrite(num1,num2);
      SendData(command);
    }   
  else if (cmd=="digitalread")
    {
      SendData(String(digitalRead(num1)));
    }    
  else if (cmd=="analogwrite")
    {
      analogWrite(num1,num2);
      SendData(command);
    }       
  else if (cmd=="analogread")
    {
      SendData(String(analogRead(num1)));
    }    
  else if (cmd=="&message")
    {
      SendData(str1+","+str2);
    }     
  else if (cmd=="+message")
    {
      SendData(str1+","+String(num2));
    }                
  else 
    {
      SendData("FAIL");
    }  
}

void SendData(String data)
{
  //Let me think about it
}
