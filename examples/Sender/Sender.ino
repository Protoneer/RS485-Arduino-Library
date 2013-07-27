// Send
#include <RS485.h>
#include <SoftwareSerial.h>


char Message[maxMsgLen+1] ;


void setup()
{
  Serial.begin(9600);
  Serial.println("System Startup - Sender");

  RS485_Begin(28800);
}

void loop()
{
  strcpy(Message,"Msg12345678901234567");

  if(RS485_SendMessage(Message,fWrite,ENABLE_PIN))
  {
    Serial.print("Sending:");
    Serial.println(Message);
  }  

  delay(1000);  
}
