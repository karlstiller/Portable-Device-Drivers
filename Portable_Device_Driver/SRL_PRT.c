/*
 * SRL_PRT.c
 *
 * Created: 30/05/2014 18:20:48
 *  Author: karl.stiller
 */ 
#include <string.h>
#include "ATMEGA2560.h"
#include "PRT_API.h"
#include "CRB_API.h"
#include "SRL_API.h"
#include "SRL_PRT.h"

void ISR_USART0_RX( void )
{
	APP_SRL_Rx();
}

void ISR_USART0_UDRE( void )
{
	APP_SRL_Tx();
}

void SRL_vEnableTx( void )
{
	WRITEREG8( UCSR0B, (READREG8(UCSR0B) | UCSR0B_UDRIE0 ));
}

void SRL_vDisableTx( void )
{
	WRITEREG8( UCSR0B, (READREG8(UCSR0B) & ~UCSR0B_UDRIE0) );
}

UINT16 SRL_wCalcBaud ( UINT16 wBaudRate)
{
	UINT32 bTemp = CPU_OSC;
	bTemp = bTemp / 8;
	bTemp = bTemp / wBaudRate;
	bTemp--;
	return bTemp;
}

void SRL_vInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, SRL_ePARITY eParity )
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
}

void SRL_vSendStr( SINT8 *abBuff )
{
	UINT8 bNrBytesSent = 0;
	while( bNrBytesSent < strlen( (char *)abBuff ) )
	{
		SRL_vSendByte( abBuff[bNrBytesSent++] );
	}
}

void SRL_vSendByte( UINT8 bByte )
{
	/* Send byte */
	WRITEREG8( UDR0, bByte );
}

UINT8 SRL_bRecvByte( void )
{
	/* Receive byte */
	return READREG8( UDR0 );
}