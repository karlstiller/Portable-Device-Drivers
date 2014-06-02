/*
 * EEP_PRT.h
 *
 * Created: 30/05/2014 17:51:22
 *  Author: karl.stiller
 */ 


#ifndef EEP_PRT_H_
#define EEP_PRT_H_

#define EEPROM_SIZE ( 4096 )
#define EEPROM_PAGE_SIZE ( 8 )

UINT8 EEP_PRT_bReadByteEEPROM( UINT16 wAddress, UINT8 *bByte );
UINT8 EEP_PRT_bWriteByteEEPROM( UINT16 wAddress, UINT8 bByte );


#endif /* EEP_PRT_H_ */