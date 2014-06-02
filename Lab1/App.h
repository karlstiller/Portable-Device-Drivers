/*
 * App.h
 *
 * Created: 20/05/2014 23:16:15
 *  Author: Karl
 */ 

#ifndef APP_H_
#define APP_H_

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

//UINT8 bInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, SRL_ePARITY eParity );
//UINT8 bSendByte( UINT8 bByte );
//UINT8 bSendStr( SINT8 *abBuff );
//UINT8 bRecvByte( void );
//UINT8 bWriteBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes );
//UINT8 bReadBufferEEPROM( UINT16 wStartAddress, UINT8 *abBuff, UINT16 wNrBytes );
//UINT8 bCalcCRC( UINT8 *abBuff, UINT8 bSizeBuff );

#endif /* APP_H_ */
