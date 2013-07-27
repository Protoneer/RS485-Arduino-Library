#include "Arduino.h"
#include <SoftwareSerial.h>

const byte RX_PIN = 2;
const byte TX_PIN = 3;
const byte ENABLE_PIN = 4;

const int maxMsgLen = 20;
const int STX = 2;
const int ETX = 3;

typedef void (*WriteCallback)  (const byte what);    // send a byte to serial port
typedef int  (*AvailableCallback)  ();    // return number of bytes available
typedef int  (*ReadCallback)  ();    // read a byte from serial port

void fWrite (const byte what);
int fAvailable ();
int fRead ();



//byte crc8 (const char *addr);

//void EncodeMessage(char message[maxMsgLen+1], unsigned char data[maxMsgLen+1+3]);

void RS485_Begin(int baud);
bool RS485_SendMessage(char message[maxMsgLen+1],WriteCallback fWrite,int EnablePin);
bool RS485_ReadMessage(AvailableCallback fAvailable, ReadCallback fRead, char data[maxMsgLen+3+1]);
bool RS485_ReadPlainMessage(AvailableCallback fAvailable, ReadCallback fRead, char message[maxMsgLen+3+1]);

