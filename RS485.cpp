#include <RS485.h>
#include "Arduino.h"

SoftwareSerial rs485 (RX_PIN, TX_PIN);

void fWrite (const byte what)
{
  rs485.write (what);  
  //Serial.print((int)what);
  //Serial.print(' ');
}

int fAvailable ()
{
  return rs485.available ();  
}

int fRead ()
{
  return rs485.read ();  
}


byte crc8 (const char *addr)
{
  byte len = 0;
  while((byte)addr[len] != '\0')
  {
    len++;
  }
  
  byte crc = 0;
  while (len--) 
    {
    byte inbyte = *addr++;
    for (byte i = 8; i; i--)
      {
      byte mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) 
        crc ^= 0x8C;
      inbyte >>= 1;
      }  // end of for
    }  // end of while
  return crc;
}  // end of crc8

void EncodeMessage(char message[maxMsgLen+1], unsigned char data[maxMsgLen+1+3])
{
  int index=0;
  int index2 = 0;
  
  data[index] = STX;
  
  while(message[index2] != '\0')
  {
    index++;
    data[index] = (char)message[index2];
    index2++;
  }
  
  index++;
  data[index] = ETX;
  
  index++;
  data[index] = (char)crc8(message);
  
  index++;
  data[index] = '\0';
}

void RS485_Begin(int baud)
{
  pinMode(ENABLE_PIN, OUTPUT);  // driver output enable
	rs485.begin(baud);
}


bool RS485_SendMessage(char message[maxMsgLen+1],WriteCallback fWrite,int EnablePin)
{  
  unsigned char temp[maxMsgLen+1+2];
  
  EncodeMessage(message,temp);
 
  digitalWrite (EnablePin, HIGH);  // enable sending
  int counter =0;
  while(temp[counter] != '\0')
  {
    fWrite(temp[counter]);
	counter++;
  }  
  
  delay(1); // Delay abit or else the RS485 will switch off before the last byte has been sent.
  digitalWrite (EnablePin, LOW);  // disable sending  
  return true;
}

bool RS485_ReadMessage(AvailableCallback fAvailable, ReadCallback fRead, char data[maxMsgLen+3+1])
{
  bool bSTX = false;
  bool bETX = false;

  byte index = 0;
  int input = -1;

  byte CRC=0;

  if(fAvailable())
  {
    while(fAvailable())
    {
      input = fRead();

      switch(input)
      {
        // Start of message
      case STX : 
        bSTX = true;
        index = 0;
        break;

        // End of message  
      case ETX : 
        bETX = true;
        break;

      default:

        if(!bSTX)
          // Don't read if the message has not started
          break;
        else
        {

          // While not the end of the message keep collection bytes
          if(!bETX)
          {
            data[index] = input;
            index++;
            if(index >= maxMsgLen+3+1)
            {
              return false;
            }
            data[index] = '\0';

          }
          else
          {
            CRC = input;    
          }  
        }            
      }
      delay(1); // Delay a bit or you will reach the end of the buffer before its even been filled.
    }

    if(CRC != crc8(data))
    {
      return false;
    }
    return true;
  }
  return false;
}

// For test the bytes comming in
bool RS485_ReadPlainMessage(AvailableCallback fAvailable, ReadCallback fRead, char message[maxMsgLen+3+1])
{
  if(fAvailable())
  {
    int input = -1;
    int counter=0;
    while(fAvailable())
    {
      input = fRead();
      message[counter] = input;
      counter++;
      message[counter] = '\0';
      delay(1); // Delay a bit or you will reach the end of the buffer before its even been filled.
    }
    return true;   
  }  
  return false;
}

