//BATTSCI Serial Functions

/************************************************************************************************************************
 * The BCM constantly sends two different 12 Byte frames to the MCM. 
 * 
 * The 1st frame has the following syntax:
 * 
 * The 2nd frame has the following syntax:
 ************************************************************************************************************************/
 
#define BATTSCI_BYTES_IN_FRAME 12

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BATTSCI_begin()
{
  pinMode(PIN_BATTSCI_DIR, OUTPUT);
  digitalWrite(PIN_BATTSCI_DIR,LOW);
  Serial2.begin(9600,SERIAL_8E1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline uint8_t BATTSCI_readByte()
{
  return Serial1.read();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline uint8_t BATTSCI_bytesAvailableForWrite()
{
  return Serial1.availableForWrite();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BATTSCI_sendFrame(uint8_t METSCIdataType, uint8_t METSCIdata, uint8_t stackVoltage, uint16_t batteryCurrent)
{
  //Verify we have at least 24B free in the serial send ring buffer

  //ping-pong between 0x87 & 0xAA frames
  uint8_t BATTSCI_Packetx87[12] =
  {
    0x87, /*Packet Type... never changes*/
    0x40, /*Never changes*/
    0x__, /*Half the battery voltage (e.g. 0x40 = d64 = 128 V*/
    0x15, /*Battery SoC (upper byte)*/
    0x6F, /*Battery SoC (lower byte)*/
    0x__, /*Battery Current (upper byte)*/
    0x__, /*Battery Current (lower byte)*/
    0x32, /* */
    0x39, /* */
    0x39, /* */
    0xmetsciState.b3, /* */
    0xchecksum /* */
  };
  
  uint8_t BATTSCI_PacketxAA[12] =
  {
    0xaa, /* */
    0x10, /* */
    0x00, /* */
    0x00, /* */
    0x00, /* */
    0x00, /* */
    0x40, /* */
    0x61, /* */
    0x__, /*Battery Current (upper byte)*/
    0x__, /*Battery Current (lower byte)*/
    0xmetsciState.b4, /* */
    0xchecksum /* */
  };


  
}

uint8_t BATTSCI_isChecksumValid( uint8_t type, uint8_t data, uint8_t checksum )
{
  if(  )
  {
    return 1; //data is valid
  } else {
    Serial.println(F("BATTSCI Bad Checksum"));
    return 0; //data invalid
  }
}
