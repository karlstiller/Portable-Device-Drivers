/*
 * SRL_API.h
 *
 * Created: 30/05/2014 18:23:54
 *  Author: karl.stiller
 */ 


#ifndef SRL_API_H_
#define SRL_API_H_

typedef enum
{
	URT_NO_PARITY = 0,
	URT_RESERVED_PARITY,
	URT_EVEN_PARITY,
	URT_ODD_PARITY,
}SRL_ePARITY;

UINT8 SRL_bInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, SRL_ePARITY eParity );
UINT8 SRL_bSendStr( SINT8 *abBuff );
UINT8 SRL_bSendByte( UINT8 bByte );
UINT8 SRL_bRecvByte( void );

#endif /* SRL_API_H_ */