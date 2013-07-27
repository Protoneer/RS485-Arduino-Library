// Receive
#include <RS485.h>
#include <SoftwareSerial.h>

char message[maxMsgLen+3+1];

void setup()
{
  Serial.begin(9600);
  Serial.println("System Startup - Receiver");

  RS485_Begin(28800);
}

void loop()
{
  //if(RS485_ReadPlainMessage(fAvailable,fRead,message))
  if(RS485_ReadMessage(fAvailable,fRead, message))
  {
    Serial.print("Receiving:");
    Serial.println(message);
  }


}





