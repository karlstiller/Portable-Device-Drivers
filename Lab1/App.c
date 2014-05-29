/* LAB 3.5 - Writing Portable Device Drivers
 * A fine example of portability
 * Fine for tool demonstration
 * Author: Karl Stiller
 * THIS FILE HAS NO PORTABLITY dependencies and should not have to
 * change for a different environment.
 */

/**********************
 * Includes           *
 **********************/
#warning remove this
#include "ATMEGA2560.h"
#include <string.h>
#include "Port.h"
#include "API_IO.h"
#include "API_Timer.h"
#include "App.h"

/**********************
 * Defines            *
 **********************/
#define DELAY_VAL   ( 0x1A )

#define EEPROM_SIZE ( 4096 )
#define EEPROM_CTRL_ADD ( EEPROM_SIZE - sizeof( tsControlEeprom ) )
#define EEPROM_PAGE_SIZE ( 8 )

/**********************
 * Global variables   *
 **********************/
U8 bDir = 1;
U8 bPrevDir = 1;
U8 bLEDS = 1;
U16 bNrInts;

/**********************
 * Functions          *
 **********************/
 
/**********************
 * EEPROM              *
 **********************/

/* Structure to use with circular buffer */
typedef struct
{
	UINT8  abBuffer[4096];
	UINT16 wMask;
	UINT16 wInsertion;
	UINT16 wRemoval;
} tsBuffCirc;

tsBuffCirc sEepromBuff;

/* Structure to control use with EEPROM */
/* Maximum of 8 bytes (1 page of EEPROM ) */
typedef struct
{
	UINT16  wNoBytesUsed;
	UINT8   bCRC;
}tsControlEeprom;

tsControlEeprom sControlEepromBackup;
tsControlEeprom sControlEeprom;

void vInitCircularBuff( tsBuffCirc *psCircularBuff )
{
	memset( psCircularBuff->abBuffer, 0, sizeof( psCircularBuff->abBuffer));
	psCircularBuff->wMask = sizeof( psCircularBuff->abBuffer) - 1;
}
 
UINT8 bAddByteBuffer( UINT8 bByte, tsBuffCirc *psCircularBuff )
{
	/* Is there space in the buffer? */
    if ( ( ( psCircularBuff->wRemoval - 1 ) & psCircularBuff->wMask ) != psCircularBuff->wInsertion )	
	{
		/* Add byte */
		psCircularBuff->abBuffer[psCircularBuff->wInsertion] = bByte;
		/* Increment pointer */
		psCircularBuff->wInsertion = (psCircularBuff->wInsertion + 1) & psCircularBuff->wMask;
		return 0;
	}
	return 1;	
}
 
UINT8 bRemoveByteBuffer( UINT8 *pByte, tsBuffCirc *psCircularBuff )
{
	/* Is buffer empty? */
	if( psCircularBuff->wInsertion == psCircularBuff->wRemoval )
	{
		return 1;
	}
	/* Read byte */
	*pByte = psCircularBuff->abBuffer[psCircularBuff->wRemoval];
	/* Increment pointer */
	psCircularBuff->wRemoval = (psCircularBuff->wRemoval + 1) & psCircularBuff->wMask;
	return 0;
}

UINT8 bReadControlStructEeprom( void )
{
	if( bReadBufferEEPROM( EEPROM_CTRL_ADD, (UINT8 *) &sControlEepromBackup, sizeof( tsControlEeprom )))
	{
		return 1;
	}
	if( bCalcCRC( (UINT8 *) &sControlEepromBackup, sizeof( tsControlEeprom ) ) )
	{
		return 1;
	}
	if( sControlEepromBackup.wNoBytesUsed == 0 )
	{
		return 1;
	}	
	sControlEeprom.wNoBytesUsed = sControlEepromBackup.wNoBytesUsed;
	return 0;
}

UINT8 bWriteControlStructEeprom( void )
{
	return bWriteBufferEEPROM( EEPROM_CTRL_ADD, (UINT8 *) &sControlEepromBackup, sizeof( sControlEepromBackup ) );
}

UINT8 bCalcCRC( UINT8 *abBuff, UINT8 bSizeBuff )
{
	UINT8 bCRC = 0;
	UINT8 bIndex = 0;
	while( bIndex < bSizeBuff )
	{
		bCRC ^= abBuff[bIndex++];
	}
	return bCRC;
}

UINT8 bUpdateControlStructEeprom( void )
{
	/* Control Structure changed? */
	if( sControlEeprom.wNoBytesUsed != sControlEepromBackup.wNoBytesUsed )
	{
		/* Update size used in EEPROM */
		sControlEepromBackup.wNoBytesUsed = sControlEeprom.wNoBytesUsed;
		/* Calculate value of CRC */
		sControlEepromBackup.bCRC = bCalcCRC( (UINT8 *)&sControlEepromBackup.wNoBytesUsed, 
		                                      sizeof( sControlEepromBackup.wNoBytesUsed ) );
		/* Write new value to control page */
		return bWriteControlStructEeprom( );
	}
	return 0;
}

UINT8 bReadByteEEPROM( UINT16 wAddress, UINT8 *bByte )
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
	*bByte = READREG8( EEDR );
	return 0;
}

UINT8 bReadBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes )
{
	UINT16 i;
	for( i = 0; i < wNrBytes; i++ )
	{
		bReadByteEEPROM( wStartAddress, &(abBuff[i]) );
		wStartAddress++;
	}
	return 0;
}

UINT8 bWriteByteEEPROM( UINT16 wAddress, UINT8 bByte )
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

UINT8 bWriteBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes )
{
	UINT16 i;
	for( i = 0; i < wNrBytes; i++ )
	{
		bWriteByteEEPROM( wStartAddress, abBuff[i] );
		wStartAddress++;
	}
	return 0;
}

/**********************
 * USART               *
 **********************/
 
UINT16 wCalcBaud ( UINT16 wBaudRate)
{
	UINT32 bTemp = CPU_OSC;
	bTemp = bTemp / 8;
	bTemp = bTemp / wBaudRate;
	bTemp--;
	return bTemp;
}

UINT8 bInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, URT_ePARITY eParity )
{
	UINT8 bUCSRC;	
	/* Parameter range checking */
	if (( wBaudRate < URT_MIN_BAUD ) || 
	    ( wBaudRate > URT_MAX_BAUD)) /* Limits for 1MHz clock */
	{
		return 1;
	}
	if (( bNoDataBits < URT_MIN_DATA_BITS ) || 
	    ( bNoDataBits > URT_MAX_DATA_BITS ))
	{
		return 1;
	}
	if (( bNoStop < URT_MIN_STOP_BITS ) ||
	    ( bNoStop > URT_MAX_STOP_BITS ))
	{
		return 1;
	}
	if (( bNoStop < URT_MIN_STOP_BITS ) ||
	( bNoStop > URT_MAX_STOP_BITS ))
	{
		return 1;
	}
	
	/* Set baud rate */	WRITEREG16( UBRR2, wCalcBaud( wBaudRate ) );
	
	/* Calculate UCSRxC value */
	bUCSRC = eParity << 4;
	bUCSRC |= ( bNoStop - 1 ) << 3;
	if( bNoDataBits > 8 )
	{
		/* Enable receiver, transmitter, and 9 bits */
		WRITEREG8( UCSR2B, UCSR2B_RXEN2 | UCSR2B_TXEN2 | UCSR2B_UCSZ22 );
		bUCSRC |= UCSR2C_UCSZ21 | UCSR2C_UCSZ20;
	}
	else
	{
		/* Enable receiver and transmitter */
		WRITEREG8( UCSR2B, UCSR2B_RXEN2 | UCSR2B_TXEN2 );
		bUCSRC |= (bNoDataBits - 5) << 1;
	}
	WRITEREG8( UCSR2A, UCSR2A_U2X2 );
	WRITEREG8( UCSR2C, bUCSRC );
	return 0;
}

UINT8 bSendStr( SINT8 *abBuff )
{
	UINT8 bNrBytesSent = 0;
	UINT8 bRet;
	while( bNrBytesSent < strlen( (char *)abBuff ) )
	{
		bRet = bSendByte( abBuff[bNrBytesSent++] );
		if ( bRet)
		{
			return bRet;
		}
	}
	return 0;
}

UINT8 bSendByte( UINT8 bByte )
{
	/* Wait for empty buffer */
	while( ! ( READREG8( UCSR2A ) & UCSR2A_UDRE2 ));
	/* Send byte */
	WRITEREG8( UDR2, bByte );
	return 0;
}

UINT8 bRecvByte( void )
{
	/* Wait for data to arrive */
	while( ! (READREG8( UCSR2A ) & UCSR2A_RXC2 ));
	/* Receive byte */
	return READREG8( UDR2 );
}
 
/*******************************************
 * void vTimerInterrupt( void )
 * Brief: Application callback function
 *        must have no parameters and return a void
 * Parameters: None
 * Return: None
 *******************************************/
void vTimerInterrupt( void )
{
	/* If key press matches count value for the key release */
	if (( bLEDS == API_IO_bReadSwitches( )) && ( bLEDS != 0 ))
	{
		/* Has direction already been changed? */
		if( bDir == bPrevDir)
		{
			/* Change direction */
			bDir = !bDir;
		}
	}
	/* Change scan value only when not equal to switches */
	else
	{
		/* Save new value of direction */
		bPrevDir = bDir;

		/* If the count direction is up */
		if( bDir )
		{
			/* Count up */
			bLEDS++;
		}
		/* Otherwise count down */
		else
		{
			/* Count down */
			bLEDS--;
		}
	}
	API_IO_bWriteLEDs( bLEDS );
	if( bNrInts > 0 )
	{
		bNrInts--;
	}
}

void delay(unsigned int val)
{
	volatile unsigned int temp;
	volatile unsigned int temp2;

	for(temp = 0; temp < val; temp++) 
		for (temp2 = 0; temp2 < val; temp2 ++) ;
}


/*******************************************
 * int main(void)                          
 * Brief: The main function                
 * Parameters: None                        
 * Return: Never returns                   
 *******************************************/
int main(void)
{
	U8 bRxCtrl = 0;
	U8 bRecord = 0;
	U8 bPlayback = 0;
	U8 bValidRecording = 0;
	U8 bSaveByte;
	U8 bTxByte;
	bNrInts = 10000;
	vInitCircularBuff( &sEepromBuff );
	/* Setup UART for 9600, 8 bits, one stop, no parity bit */
	if( bInitUart( 9600, 8, 1, URT_NO_PARITY ) == 0 )
	{
		API_IO_bInitIO();
		//API_Timer_bInitializeTimer( vTimerInterrupt, DELAY_VAL );
	}
	else
	{
		API_IO_bWriteLEDs( 1 );
	}
	PORT_bEnableInterrupts();
	bValidRecording = !bReadControlStructEeprom();
	if( !bValidRecording )
	{
		sControlEeprom.wNoBytesUsed = 0;
		bUpdateControlStructEeprom();
	}
	while( 1 )
	{
		bSaveByte = 1;
		U8 bRxByte = bRecvByte();
		switch ( bRxByte )
		{
			case '\r':
			{
				bSendByte( '\n' );
				bRxCtrl = 0;
				break;
			}
			case '\n':
			{
				bSendByte( '\r' );
				bRxCtrl = 0;
				break;
			}
			case '^':
			{
				bSaveByte = 0;
				bRxCtrl = 1;
				break;
			}
			case BACKSPACE:
			{
				if( sControlEeprom.wNoBytesUsed )
				{
					sControlEeprom.wNoBytesUsed--;
					bUpdateControlStructEeprom();
					API_IO_bWriteLEDs( sControlEeprom.wNoBytesUsed );
					bSaveByte = 0;
					bRxCtrl = 0;
				}
			}
			case '?':
			{
				if( bRxCtrl )
				{
					U16 wNrBytes = sControlEeprom.wNoBytesUsed;
					U8 abNrBytesStr[30];
					U8 bTemp;
					bSaveByte = 0;
					/* Tens of thousands */
					bTemp = wNrBytes / 10000;
					wNrBytes -= bTemp * 10000;
					abNrBytesStr[0] = '0' + bTemp;
					/* Thousands */
					bTemp = wNrBytes / 1000;
					wNrBytes -= bTemp * 1000;
					abNrBytesStr[1] = '0' + bTemp;
					/* Hundreds */
					bTemp = wNrBytes / 100;
					wNrBytes -= bTemp * 100;
					abNrBytesStr[2] = '0' + bTemp;
					/* Tens */
					bTemp = wNrBytes / 10;
					wNrBytes -= bTemp * 10;
					abNrBytesStr[3] = '0' + bTemp;
					/* Unit */
					abNrBytesStr[4] = '0' + wNrBytes;
					/* New Line */
					abNrBytesStr[5] = '\r';
					abNrBytesStr[5] = '\n';
					abNrBytesStr[5] = 0;
					bSendStr((S8 *)abNrBytesStr);
				}
			}
			case 'Y':
			case 'y':
			{
				if( bRxCtrl )
				{
					bPlayback = 1;
					bRxCtrl = 0;
					bSaveByte = 0;
				}				
				break;
			}
			case 'Z':
			case 'z':
			{
				if( bRxCtrl )
				{
					bRecord = bRecord ^ 1;
					bRxCtrl = 0;
					bSaveByte = 0;
					if( bRecord )
					{
						sControlEeprom.wNoBytesUsed = 0;
					}
				}
				break;
			}
			
			default:
				bRxCtrl = 0;
				break;	
		}
		bSendByte( bRxByte );
		
		if( bSaveByte && bRecord )
		{
			if( bAddByteBuffer( bRxByte, &sEepromBuff ) == 0 )
			{
				if( bRemoveByteBuffer( &bRxByte, &sEepromBuff ) == 0 )
				{
					if( bWriteByteEEPROM( sControlEeprom.wNoBytesUsed, bRxByte ) == 0 )
					{
						sControlEeprom.wNoBytesUsed++;
						bUpdateControlStructEeprom();
						bValidRecording = 1;
					}
				}
			}
		}
		if( bPlayback )
		{
			if( bValidRecording )
			{
				for( U16 i = 0; i < sControlEeprom.wNoBytesUsed; i++ )
				{
					/* Send Recorded bytes */
					if( bReadByteEEPROM( i, &bTxByte ) == 0 ) 
					{
						bSendByte( bTxByte );
						delay( 100 );
					}
				}
				bPlayback = 0;
			}
		}
	}
    /* Be nice to the compiler */
	return 0;
}

