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

void SRL_vInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, SRL_ePARITY eParity );
void  SRL_vSendStr( SINT8 *abBuff );
void  SRL_vSendByte( UINT8 bByte );
UINT8 SRL_bRecvByte( void );
void  SRL_vEnableTx( void );
void  SRL_vDisableTx( void );

extern void APP_SRL_Rx( void );
extern void APP_SRL_Tx( void );

#endif /* SRL_API_H_ */