/*
 * EEP_API.c
 *
 * Created: 30/05/2014 17:23:14
 *  Author: karl.stiller
 */ 
#include "Port.h"
#include "EEP_PRT.h"
#include "EEP_API.h"
#include "CRB_API.h"

EEP_API_tsControlEeprom EEP_API_sControlEepromBackup;
EEP_API_tsControlEeprom EEP_API_sControlEeprom;

UINT8 EEP_API_bReadControlStructEeprom( void )
{
	if( EEP_API_bReadBufferEEPROM( EEPROM_CTRL_ADD, (UINT8 *) &EEP_API_sControlEepromBackup, sizeof( EEP_API_tsControlEeprom )))
	{
		return 1;
	}
	if( EEP_API_bCalcCRC( (UINT8 *) &EEP_API_sControlEepromBackup, sizeof( EEP_API_tsControlEeprom ) ) )
	{
		return 1;
	}
	if( EEP_API_sControlEepromBackup.wNoBytesUsed == 0 )
	{
		return 1;
	}
	EEP_API_sControlEeprom.wNoBytesUsed = EEP_API_sControlEepromBackup.wNoBytesUsed;
	return 0;
}

UINT8 EEP_API_bWriteControlStructEeprom( void )
{
	UINT16 i;
	UINT16 wStartAddress = EEPROM_CTRL_ADD;
	UINT8 *pByte = (UINT8 *)&EEP_API_sControlEepromBackup;
	for( i = 0; i < sizeof( EEP_API_sControlEepromBackup ); i++ )
	{
		EEP_API_bWriteByteEEPROM( wStartAddress++, *pByte );
		pByte++;
	}
	return 0;	

}

UINT8 EEP_API_bCalcCRC( UINT8 *abBuff, UINT8 bSizeBuff )
{
	UINT8 bCRC = 0;
	UINT8 bIndex = 0;
	while( bIndex < bSizeBuff )
	{
		bCRC ^= abBuff[bIndex++];
	}
	return bCRC;
}

UINT8 EEP_API_bUpdateControlStructEeprom( void )
{
	/* Control Structure changed? */
	if( EEP_API_sControlEeprom.wNoBytesUsed != EEP_API_sControlEepromBackup.wNoBytesUsed )
	{
		/* Update size used in EEPROM */
		EEP_API_sControlEepromBackup.wNoBytesUsed = EEP_API_sControlEeprom.wNoBytesUsed;
		/* Calculate value of CRC */
		EEP_API_sControlEepromBackup.bCRC = EEP_API_bCalcCRC( (UINT8 *)&EEP_API_sControlEepromBackup.wNoBytesUsed,
		sizeof( EEP_API_sControlEepromBackup.wNoBytesUsed ) );
		/* Write new value to control page */
		return EEP_API_bWriteControlStructEeprom( );
	}
	return 0;
}

UINT8 EEP_API_bReadBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes )
{
	UINT16 i;
	for( i = 0; i < wNrBytes; i++ )
	{
		EEP_API_bReadByteEEPROM( wStartAddress, &(abBuff[i]) );
		wStartAddress++;
	}
	return 0;
}

UINT8 EEP_API_bWriteByteEEPROM( UINT16 wAddress, UINT8 bByte )
{
	return EEP_PRT_bWriteByteEEPROM( wAddress, bByte);
}

UINT8 EEP_API_bReadByteEEPROM( UINT16 wAddress, UINT8 *pByte )     
{
	return EEP_PRT_bReadByteEEPROM( wAddress, pByte );
}