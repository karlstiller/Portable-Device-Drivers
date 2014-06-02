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
#include "Port.h"
#include "API_IO.h"
#include "API_Timer.h"
#include "CRB_API.h"
#include "EEP_API.h"
#include "SRL_API.h"
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
U16 bNrInts;

/**********************
 * Functions          *
 **********************/
 
 
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
	CRB_API_vInitCircularBuff( &EEP_API_sEepromBuff );
	/* Setup UART for 9600, 8 bits, one stop, no parity bit */
	if( SRL_bInitUart( 9600, 8, 1, URT_NO_PARITY ) == 0 )
	{
		API_IO_bInitIO();
		API_Timer_bInitializeTimer( vTimerInterrupt, DELAY_VAL );
	}
	else
	{
		API_IO_bWriteLEDs( 1 );
	}
	PORT_bEnableInterrupts();
	bValidRecording = !EEP_API_bReadControlStructEeprom();
	if( !bValidRecording )
	{
		EEP_API_sControlEeprom.wNoBytesUsed = 0;
		EEP_API_bUpdateControlStructEeprom();
	}
	while( 1 )
	{
		bSaveByte = 1;
		U8 bRxByte = SRL_bRecvByte();
		switch ( bRxByte )
		{
			case '\r':
			{
				SRL_bSendByte( '\n' );
				bRxCtrl = 0;
				break;
			}
			case '\n':
			{
				SRL_bSendByte( '\r' );
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
				if( EEP_API_sControlEeprom.wNoBytesUsed )
				{
					EEP_API_sControlEeprom.wNoBytesUsed--;
					EEP_API_bUpdateControlStructEeprom();
					API_IO_bWriteLEDs( EEP_API_sControlEeprom.wNoBytesUsed );
					bSaveByte = 0;
					bRxCtrl = 0;
				}
			}
			case 'N':
			case 'n':
			{
				if( bRxCtrl )
				{
					U16 wNrBytes = EEP_API_sControlEeprom.wNoBytesUsed;
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
					SRL_bSendStr((S8 *)abNrBytesStr);
				}
				break;
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
						EEP_API_sControlEeprom.wNoBytesUsed = 0;
					}
				}
				break;
			}
			
			default:
				bRxCtrl = 0;
				break;	
		}
		SRL_bSendByte( bRxByte );
		
		if( bSaveByte && bRecord )
		{
			if( CRB_API_bAddByteBuffer( bRxByte, &EEP_API_sEepromBuff ) == 0 )
			{
				if( CRB_API_bRemoveByteBuffer( &bRxByte, &EEP_API_sEepromBuff ) == 0 )
				{
					if( EEP_API_bWriteByteEEPROM( EEP_API_sControlEeprom.wNoBytesUsed, bRxByte ) == 0 )
					{
						EEP_API_sControlEeprom.wNoBytesUsed++;
						EEP_API_bUpdateControlStructEeprom();
						bValidRecording = 1;
					}
				}
			}
		}
		if( bPlayback )
		{
			if( bValidRecording )
			{
				for( U16 i = 0; i < EEP_API_sControlEeprom.wNoBytesUsed; i++ )
				{
					/* Send Recorded bytes */
					if( EEP_API_bReadByteEEPROM( i, &bTxByte ) == 0 ) 
					{
						SRL_bSendByte( bTxByte );
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
