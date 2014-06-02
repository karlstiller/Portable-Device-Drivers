/*
 * SRL_PRT.c
 *
 * Created: 30/05/2014 18:20:48
 *  Author: karl.stiller
 */ 
#include "ATMEGA2560.h"
#include "Port.h"
#include <string.h>
#include "SRL_API.h"
#include "SRL_PRT.h"


UINT16 SRL_wCalcBaud ( UINT16 wBaudRate)
{
	UINT32 bTemp = CPU_OSC;
	bTemp = bTemp / 8;
	bTemp = bTemp / wBaudRate;
	bTemp--;
	return bTemp;
}

UINT8 SRL_PRT_bInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, SRL_ePARITY eParity )
{
	UINT8 bUCSRC;
	/* Set baud rate */	WRITEREG16( UBRR0, SRL_wCalcBaud( wBaudRate ) );
		
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
		/* Enable receiver and transmitter */
		WRITEREG8( UCSR0B, UCSR0B_RXEN0 | UCSR0B_TXEN0 );
		bUCSRC |= (bNoDataBits - 5) << 1;
	}
	WRITEREG8( UCSR0A, UCSR0A_U2X0 );
	WRITEREG8( UCSR0C, bUCSRC );
	return 0;
}

UINT8 SRL_bSendStr( SINT8 *abBuff )
{
	UINT8 bNrBytesSent = 0;
	UINT8 bRet;
	while( bNrBytesSent < strlen( (char *)abBuff ) )
	{
		bRet = SRL_bSendByte( abBuff[bNrBytesSent++] );
		if ( bRet)
		{
			return bRet;
		}
	}
	return 0;
}

UINT8 SRL_bSendByte( UINT8 bByte )
{
	/* Wait for empty buffer */
	while( ! ( READREG8( UCSR0A ) & UCSR0A_UDRE0 ));
	/* Send byte */
	WRITEREG8( UDR0, bByte );
	return 0;
}

UINT8 SRL_bRecvByte( void )
{
	/* Wait for data to arrive */
	while( ! (READREG8( UCSR0A ) & UCSR0A_RXC0 ));
	/* Receive byte */
	return READREG8( UDR0 );
}