/*
 * EEP_Port.c
 *
 * Created: 30/05/2014 17:21:38
 *  Author: karl.stiller
 */
#include "ATMEGA2560.h" 
#include "Port.h"
#include "EEP_PRT.h"

UINT8 EEP_PRT_bReadByteEEPROM( UINT16 wAddress, UINT8 *pByte )
{
	/* Test limit */
	if( wAddress > EEPROM_SIZE - 1 )
	{
		return 1;
	}
	/* Wait for completion of previous write */
	while( READREG8( EECR ) & EECR_EEPE);
	/* Set up address register */
	WRITEREG16( EEAR, wAddress );
	/* Start EEPROM read by writing EERE */
	WRITEREG8( EECR, READREG8( EECR ) | EECR_EERE );
	/* Return data from Data Register */
	*pByte = READREG8( EEDR );
	return 0;
}

UINT8 EEP_PRT_bWriteByteEEPROM( UINT16 wAddress, UINT8 bByte )
{
	/* Test limit */
	if( wAddress > EEPROM_SIZE - 1 )
	{
		return 1;
	}
	/* Wait for completion of previous write */
	while( READREG8( EECR ) & EECR_EEPE );
	/* Set up address and Data Registers */
	WRITEREG16( EEAR, wAddress );
	WRITEREG8( EEDR, bByte);
	/* Make sure that the set to EEMPE and EEPE occur within 4 clock cycles */
	/* Otherwise write will fail */
	PORT_bDisableInterrupts();
	/* Write logical one to EEMPE */
	ORREG8( EECR, EECR_EEMPE);
	
	/* Start EEPROM write by setting EEPE */
	ORREG8( EECR, EECR_EEPE );
	PORT_bEnableInterrupts();
	return 0;
}
