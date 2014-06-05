/*
 * SRL_PRT.h
 *
 * Created: 30/05/2014 18:34:37
 *  Author: karl.stiller
 */ 


#ifndef SRL_PRT_H_
#define SRL_PRT_H_

#define CPU_OSC			( 1000000 )	/* 1 MHz on-board RC oscillator (default)*/
#define URT_MAX_BAUD	( 62500 )	/* Maximum and minimum values for each clock */
#define URT_MIN_BAUD	( 2400 )	/* frequency is defined on page 223 of data sheet */

#define URT_MIN_DATA_BITS ( 5 )
#define URT_MAX_DATA_BITS ( 9 )
#define URT_MIN_STOP_BITS ( 1 )
#define URT_MAX_STOP_BITS ( 2 )

void SRL_PRT_vInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, SRL_ePARITY eParity );

#endif /* SRL_PRT_H_ */