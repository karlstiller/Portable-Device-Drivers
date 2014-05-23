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
#include "Port.h"
#include "API_IO.h"
#include "API_Timer.h"
#include "App.h"

/**********************
 * Defines            *
 **********************/
#define DELAY_VAL   ( 0x1A )

/**********************
 * Global variables   *
 **********************/
U8 bDir = 1;
U8 bPrevDir = 1;
U8 bLEDS = 1;

/**********************
 * Functions          *
 **********************/

UINT16 wCalcBaud ( UINT16 wBaudRate)
{
	return (CPU_OSC / ( 16 * wBaudRate)) - 1;
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
	
	/* Set baud rate */	WRITEREG16( UBRR0, wCalcBaud( wBaudRate ) );
	
	/* Calculate UCSRxC value */
	bUCSRC = eParity << 4;
	bUCSRC |= bNoStop << 3;
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
	WRITEREG8( UCSR0C, bUCSRC );
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


/*******************************************
 * int main(void)                          
 * Brief: The main function                
 * Parameters: None                        
 * Return: Never returns                   
 *******************************************/
int main(void)
{
	API_IO_bInitIO();
	API_Timer_bInitializeTimer( vTimerInterrupt, DELAY_VAL );
	/* Setup UART for 9600, 8 bits, one stop, no parity bit */
	if( bInitUart( 9600, 8, 1, URT_NO_PARITY ))
	{
		API_IO_bWriteLEDs( 1 );
		while( 1 );
	}
	bSendByte( 'H' );
	bSendByte( 'e' );
	bSendByte( 'l' );
	bSendByte( 'l' );
	bSendByte( 'o' );
	bSendByte( ' ' );
	bSendByte( 'W' );
	bSendByte( 'o' );
	bSendByte( 'r' );
	bSendByte( 'l' );
	bSendByte( 'd' );
	bSendByte( '!' );
	while( 1 )
	{
        /* The operational code is contained in the interrupt functions */
	}
    /* Be nice to the compiler */
	return 0;
}

