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
U8 bPlayback;
U8 bRecord;
U8 bTxFlag;
U16 wTxAddressEeprom;
U8 bValidRecording;

/**********************
 * Functions          *
 **********************/
 
/**********************
 * EEPROM              *
 **********************/

UINT8  bEepromBuff[EEPROM_CTRL_ADD];
UINT16 wNoEepromBuff;

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

UINT8 bInitEeprom( void )
{
	wNoEepromBuff = 0;
	return 0;
}

/**********************
 * USART              *
 **********************/
 
tsBuffCirc sKbdBuff;
 
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
	/* App Level */
	bPlayback = 0;
	bRecord = 0;
	bTxFlag = 0;
	
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
	
	/* Set baud rate */	WRITEREG16( UBRR0, wCalcBaud( wBaudRate ) );
	
	/* Calculate UCSRxC value */
	bUCSRC = eParity << 4;
	bUCSRC |= ( bNoStop - 1 ) << 3;
	if( bNoDataBits > 8 )
	{
		/* Enable receiver, transmitter, and 9 bits */
		WRITEREG8( UCSR0B, UCSR0B_RXEN0 | UCSR0B_TXEN0 | UCSR0B_UCSZ02 );
		bUCSRC |= UCSR0C_UCSZ01 | UCSR0C_UCSZ00;
	}
	else
	{
		/* Enable uart tx rx and rx interrupts. */
		WRITEREG8( UCSR0B, UCSR0B_RXEN0 | UCSR0B_TXEN0 | UCSR0B_RXCIE0 );
		bUCSRC |= (bNoDataBits - 5) << 1;
	}
	WRITEREG8( UCSR0A, UCSR0A_U2X0 );
	WRITEREG8( UCSR0C, bUCSRC );
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
	while( ! ( READREG8( UCSR0A ) & UCSR0A_UDRE0 ));
	/* Send byte */
	WRITEREG8( UDR0, bByte );
	return 0;
}

UINT8 bRecvByte( void )
{
	/* Wait for data to arrive */
	while( ! (READREG8( UCSR0A ) & UCSR0A_RXC0 ));
	/* Receive byte */
	return READREG8( UDR0 );
}

void ISR_USART0_RX( void )
{
	static UINT8 bRxCtrl = 0;
	UINT8 bSaveByte = 1;
	UINT8 bCarriageExtension = 0;
	
	// Get byte
	UINT8 bRxByte = READREG8( UDR0 );
	API_IO_bWriteLEDs( bRxByte );
	//bSendByte( bRxByte );
	/*
	// Add byte to Keyboard Buffer 
	bAddByteBuffer( bRxByte, &sKbdBuff );
	
	// Check what needs to be done for this byte 
	switch ( bRxByte )
	{
		// Carriage feed extension characters
		case '\r':
		{
			bAddByteBuffer( '\n', &sKbdBuff );
			if( bRecord )
			{
				bCarriageExtension = 1; 
			}
			bRxCtrl = 0;
			break;
		}
		case '\n':
		{
			bAddByteBuffer( '\r', &sKbdBuff );
			if( bRecord )
			{
				bCarriageExtension = 1;
			}			
			bRxCtrl = 0;
			break;
		}
		case '^':
		{
			bRxCtrl = 1;
			break;
		}
		case BACKSPACE:
		{
			if( sControlEeprom.wNoBytesUsed )
			{
				sControlEeprom.wNoBytesUsed--;
				bUpdateControlStructEeprom();
			}
			bSaveByte = 0;
			bRxCtrl = 0;
		}
		case '?':
		{
			if( bRxCtrl )
			{
				U16 wNrBytes = sControlEeprom.wNoBytesUsed;
				U8 bTemp;
				bSaveByte = 0;
				// Tens of thousands 
				bTemp = wNrBytes / 10000;
				wNrBytes -= bTemp * 10000;
				bAddByteBuffer( ( '0' + bTemp ), &sKbdBuff );
				// Thousands
				bTemp = wNrBytes / 1000;
				wNrBytes -= bTemp * 1000;
				bAddByteBuffer( ( '0' + bTemp ), &sKbdBuff );
				// Hundreds 
				bTemp = wNrBytes / 100;
				wNrBytes -= bTemp * 100;
				bAddByteBuffer( ( '0' + bTemp ), &sKbdBuff );
				// Tens 
				bTemp = wNrBytes / 10;
				wNrBytes -= bTemp * 10;
				bAddByteBuffer( ( '0' + bTemp ), &sKbdBuff );
				// Unit
				bAddByteBuffer( ( '0' + bTemp ), &sKbdBuff );
				// New Line 
				bAddByteBuffer( '\r', &sKbdBuff );
				bAddByteBuffer( '\n', &sKbdBuff );
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
				wTxAddressEeprom = 0;
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
		{
			bRxCtrl = 0;
		}
	}
	if( bCarriageExtension )
	{
		bWriteByteEEPROM( sControlEeprom.wNoBytesUsed++, '\r' );
		bWriteByteEEPROM( sControlEeprom.wNoBytesUsed++, '\n' );
		bUpdateControlStructEeprom();
	}
	else if( bRecord && bSaveByte )
	{
		bWriteByteEEPROM( sControlEeprom.wNoBytesUsed++, bRxByte );
		bUpdateControlStructEeprom();
	}
	//Enable Tx complete interrupt
	WRITEREG8( UCSR0B, (READREG8(UCSR0B) | UCSR0B_TXCIE0 ));
	bRemoveByteBuffer( &bRxByte, &sKbdBuff );
	bSendByte( bRxByte );
	*/
	WRITEREG8( UCSR0B, (READREG8(UCSR0B) | UCSR0B_UDRIE0 ));
}

/* Function to send recorded data back */
void ISR_USART0_TX( void )
{
	WRITEREG8( UCSR0B, (READREG8(UCSR0B) & ~UCSR0B_TXCIE0) );
}

/* Function to send echo */
void ISR_USART0_UDRE( void )
{
	/*
	UINT8 bTxByte;
	if( bRemoveByteBuffer( &bTxByte, &sKbdBuff ) == 0 )
	{
		// Send byte 
		WRITEREG8( UDR0, bTxByte );
	}
	else if(( bPlayback ) && ( bValidRecording ))
	{
		// Send Recorded byte
		if( bReadByteEEPROM( wTxAddressEeprom, &bTxByte ) == 0 )
		{
			// Send byte
			WRITEREG8( UDR0, bTxByte );
			// Reached end of saved buffer?
			if( wTxAddressEeprom >= sControlEeprom.wNoBytesUsed )
			{
				// Stop sending buffer 
				bPlayback = 0;
			}
		}
	}
	else
	{
		// Disable Tx complete interrupt
		WRITEREG8( UCSR0B, (READREG8(UCSR0B) & ~UCSR0B_TXCIE0) );
	}
	*/
	API_IO_bWriteLEDs( 0xA5 );
	//WRITEREG8( UCSR0B, (READREG8(UCSR0B) & ~UCSR0B_TXCIE0) );
	WRITEREG8( UDR0, 'A' );	
	
	WRITEREG8( UCSR0B, (READREG8(UCSR0B) & ~UCSR0B_UDRIE0) );
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
	vInitCircularBuff( &sKbdBuff );
	/* Setup UART for 9600, 8 bits, one stop, no parity bit */
	if( bInitUart( 9600, 8, 1, URT_NO_PARITY ) == 0 )
	{
		API_IO_bInitIO();
		API_Timer_bInitializeTimer( vTimerInterrupt, DELAY_VAL );
	}
	else
	{
		API_IO_bWriteLEDs( 1 );
	}
	bValidRecording = !bReadControlStructEeprom();
	if( !bValidRecording )
	{
		sControlEeprom.wNoBytesUsed = 0;
		bUpdateControlStructEeprom();
	}
	PORT_bEnableInterrupts();
	while( 1 )
	{
		delay( 0xFFFF );
	}
    /* Be nice to the compiler */
	return 0;
}

