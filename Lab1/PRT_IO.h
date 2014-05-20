/*
 * PRT_IO.h
 *
 * Created: 19/05/2014 22:13:36
 *  Author: Karl
 */ 
#ifndef PRT_IO_H_
#define PRT_IO_H_

#include "ATMEGA2560.h"

#define SWITCHES		(PIND)
#define SWITCHES_DIR	(DDRD)

#define LEDS			(PORTB)
#define LEDS_DIR		(DDRB)

UINT8 PRT_IO_bInitIO( void );
UINT8 PRT_IO_bReadSwitches( void );
UINT8 PRT_IO_bWriteLEDs( UINT8 bVal );


#endif /* PRT_IO_H_ */