/*
 * App.h
 *
 * Created: 20/05/2014 23:16:15
 *  Author: Karl
 */ 

#ifndef APP_H_
#define APP_H_

#define CPU_OSC ( 1000000 )  /* 1 MHz on-board RC oscillator (default)*/

#define URT_MAX_BAUD ( 62500 ) /* Maximum and minimum values for each clock */
#define URT_MIN_BAUD ( 2400 ) /* frequency is defined on page 223 of data sheet */
#define URT_MIN_DATA_BITS ( 5 )
#define URT_MAX_DATA_BITS ( 9 )
#define URT_MIN_STOP_BITS ( 1 )
#define URT_MAX_STOP_BITS ( 2 )

#define BACKSPACE (0x7F) /* On my keyboard it is 'DEL' and not 0x08 'BS' */

/* Note that I am deliberately defining different variable types for the
 * application space
 */
#define U32 unsigned long
#define S32 signed long
#define U16 unsigned short
#define S16 signed short
#define U8 unsigned char
#define S8 signed char

/* Structure to control use with EEPROM */
typedef struct
{
	UINT16  wNoBytesUsed;
	UINT8   bCRC;
}tsControlEeprom;

/* Structure to use with circular buffer */
typedef struct
{
	UINT8  abBuffer[32];
	UINT16 wMask;
	UINT16 wInsertion;
	UINT16 wRemoval;
} tsBuffCirc;

typedef enum 
{
	URT_NO_PARITY = 0,
	URT_RESERVED_PARITY,
	URT_EVEN_PARITY,
	URT_ODD_PARITY,	
}URT_ePARITY;

UINT8 bInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, URT_ePARITY eParity );
UINT8 bSendByte( UINT8 bByte );
UINT8 bSendStr( SINT8 *abBuff );
UINT8 bRecvByte( void );
UINT8 bWriteBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes );
UINT8 bReadBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes );
UINT8 bCalcCRC( UINT8 *abBuff, UINT8 bSizeBuff );

/* vectors in AVR are hard coded to a function by name */
/* USART0 Rx Complete */
extern void ISR_USART0_RX (void) __attribute__ ((signal));
/* USART0 Data Register Empty */
extern void ISR_USART0_UDRE (void) __attribute__ ((signal));
/* USART0 Tx Complete */
extern void ISR_USART0_TX (void) __attribute__ ((signal));

extern void __vector_24 (void) __attribute__ ((signal));

#endif /* APP_H_ */
