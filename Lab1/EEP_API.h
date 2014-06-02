/*
 * EEP_API.h
 *
 * Created: 30/05/2014 17:26:38
 *  Author: karl.stiller
 */ 


#ifndef EEP_API_H_
#define EEP_API_H_

/* Structure to control use with EEPROM */
/* Maximum of 8 bytes (1 page of EEPROM ) */

#define EEPROM_CTRL_ADD ( EEPROM_SIZE - sizeof( EEP_API_tsControlEeprom ) )

typedef struct
{
	UINT16  wNoBytesUsed;
	UINT8   bCRC;
}EEP_API_tsControlEeprom;

extern CRB_API_tsBuffCirc EEP_API_sEepromBuff;
extern EEP_API_tsControlEeprom EEP_API_sControlEeprom;

UINT8 EEP_API_bReadControlStructEeprom( void );
UINT8 EEP_API_bWriteControlStructEeprom( void );
UINT8 EEP_API_bCalcCRC( UINT8 *abBuff, UINT8 bSizeBuff );
UINT8 EEP_API_bUpdateControlStructEeprom( void );
UINT8 EEP_API_bReadBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes );
UINT8 EEP_API_bWriteByteEEPROM( UINT16 wAddress, UINT8 bByte );
UINT8 EEP_API_bReadByteEEPROM( UINT16 wAddress, UINT8 *pByte );

#endif /* EEP_API_H_ */