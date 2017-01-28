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
#include "PRT_API.h"
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
U8 bPlayback;
U8 bRecord;
U8 bTxFlag;
U16 wTxAddressEeprom;
U8 bValidRecording;

CRB_API_tsBuffCirc sKbdBuff;

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
}

void APP_SRL_Rx( void )
{
	static UINT8 bRxCtrl = 0;
	UINT8 bSaveByte = 1;

	// Get byte
	UINT8 bRxByte = SRL_bRecvByte();

	// Add byte to Keyboard Buffer
	CRB_API_bAddByteBuffer( bRxByte, &sKbdBuff );

	// Check what needs to be done for this byte
	switch ( bRxByte )
	{
		// Carriage feed extension characters
		case '\r':
		case '\n':
		{
			CRB_API_bAddByteBuffer( '\r', &sKbdBuff );
			CRB_API_bAddByteBuffer( '\n', &sKbdBuff );
			if( bRecord )
			{
				if( EEP_API_sControlEeprom.wNoBytesUsed < EEPROM_CTRL_ADD )
				{
					EEP_API_bWriteByteEEPROM( EEP_API_sControlEeprom.wNoBytesUsed++, '\r' );
					EEP_API_bWriteByteEEPROM( EEP_API_sControlEeprom.wNoBytesUsed++, '\n' );
					EEP_API_bUpdateControlStructEeprom();
				}
			}
			bRxCtrl = 0;
			break;
		}
		case '^':
		{
			bRxCtrl = 1;
			bSaveByte = 0;
			break;
		}
		case BACKSPACE:
		{
			if( EEP_API_sControlEeprom.wNoBytesUsed )
			{
				EEP_API_sControlEeprom.wNoBytesUsed--;
				EEP_API_bUpdateControlStructEeprom();
			}
			bSaveByte = 0;
			bRxCtrl = 0;
		}
		case 'N':
		case 'n':
		{
			if( bRxCtrl )
			{
				UINT16 wNrBytes = EEP_API_sControlEeprom.wNoBytesUsed;
				UINT8 bTemp[4];
				bSaveByte = 0;
				// Unit
				bTemp[3] = wNrBytes % 10;
				wNrBytes = wNrBytes - bTemp[3];
				// Tens
				wNrBytes = wNrBytes / 10;
				bTemp[2] = wNrBytes % 10;
				wNrBytes = wNrBytes - bTemp[2];
				// Hundreds
				wNrBytes = wNrBytes / 10;
				bTemp[1] = wNrBytes % 10;
				wNrBytes = wNrBytes - bTemp[1];
				// Thousands
				wNrBytes = wNrBytes / 10;
				bTemp[0] = wNrBytes % 10;
				wNrBytes = wNrBytes - bTemp[0];

				CRB_API_bAddByteBuffer( ( '0' + bTemp[0] ), &sKbdBuff );
				CRB_API_bAddByteBuffer( ( '0' + bTemp[1] ), &sKbdBuff );
				CRB_API_bAddByteBuffer( ( '0' + bTemp[2] ), &sKbdBuff );
				CRB_API_bAddByteBuffer( ( '0' + bTemp[3] ), &sKbdBuff );
				break;
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
					EEP_API_sControlEeprom.wNoBytesUsed = 0;
				}
			}
			break;
		}
		default:
		{
			bRxCtrl = 0;
		}
	}
	if( bRecord && bSaveByte )
	{
		if( EEP_API_sControlEeprom.wNoBytesUsed < EEPROM_CTRL_ADD )
		{
			EEP_API_bWriteByteEEPROM( EEP_API_sControlEeprom.wNoBytesUsed++, bRxByte );
			EEP_API_bUpdateControlStructEeprom();
		}
		else
		{
			CRB_API_bAddByteBuffer( '*',  &sKbdBuff );
			CRB_API_bAddByteBuffer( '*',  &sKbdBuff );
			CRB_API_bAddByteBuffer( 'F',  &sKbdBuff );
			CRB_API_bAddByteBuffer( 'U',  &sKbdBuff );
			CRB_API_bAddByteBuffer( 'L',  &sKbdBuff );
			CRB_API_bAddByteBuffer( 'L',  &sKbdBuff );
			CRB_API_bAddByteBuffer( '*',  &sKbdBuff );
			CRB_API_bAddByteBuffer( '*',  &sKbdBuff );
			CRB_API_bAddByteBuffer( '\r', &sKbdBuff );
			CRB_API_bAddByteBuffer( '\n', &sKbdBuff );
		}
	}
	//Enable Tx interrupt
	SRL_vEnableTx();
}

void APP_SRL_Tx( void )
{
	UINT8 bTxByte;
	if( CRB_API_bRemoveByteBuffer( &bTxByte, &sKbdBuff ) == 0 )
	{
		// Send byte
		SRL_vSendByte( bTxByte );
	}
	else if(( bPlayback ) && ( bValidRecording ))
	{
		// Send Recorded byte
		if( EEP_API_bReadByteEEPROM( wTxAddressEeprom++, &bTxByte ) == 0 )
		{
			// Send byte
			SRL_vSendByte( bTxByte );
			// Reached end of saved buffer?
			if( wTxAddressEeprom >= EEP_API_sControlEeprom.wNoBytesUsed )
			{
				// Stop sending buffer
				bPlayback = 0;
			}
		}
	}
	else
	{
		// Disable Tx interrupt
		SRL_vDisableTx();
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
	//U8 bRxCtrl = 0;
	//U8 bRecord = 0;
	//U8 bPlayback = 0;
	U8 bValidRecording = 0;
	//U8 bSaveByte;
	//U8 bTxByte;
	CRB_API_vInitCircularBuff( &sKbdBuff );
	/* Setup UART for 9600, 8 bits, one stop, no parity bit */
	SRL_vInitUart( 9600, 8, 1, URT_NO_PARITY );
	API_IO_bInitIO();
	API_Timer_bInitializeTimer( vTimerInterrupt, DELAY_VAL );

	bValidRecording = !EEP_API_bReadControlStructEeprom();
	if( !bValidRecording )
	{
		EEP_API_sControlEeprom.wNoBytesUsed = 0;
		EEP_API_bUpdateControlStructEeprom();
	}
	PRT_bEnableInterrupts();
	while( 1 )
	{
		delay( 0xFFFF );
	}
    /* Be nice to the compiler */
	return 0;
}
