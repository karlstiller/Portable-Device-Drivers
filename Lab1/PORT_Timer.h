/*
 * PORT_Timer.h
 *
 * Created: 19/05/2014 21:45:49
 *  Author: Karl
 */ 
#ifndef PRT_TIMER0_H_
#define PRT_TIMER0_H_

#include "Port.h"

UINT8 PRT_Timer_Set_Callback( void ( *pTimerFunc)( void ) );
UINT8 PRT_Timer_InitializeTimer( UINT8 bVal );
UINT8 PRT_Timer_bGenerate_Interrupt( void );
UINT8 PRT_Timer_bTest_Callback( void );

/* vectors in AVR are hard coded to a function by name */
extern void ISR_TIMER0_COMPA (void) __attribute__ ((interrupt));
extern void ISR_TIMER0_COMPB (void) __attribute__ ((interrupt));
extern void ISR_TIMER0_OVF (void) __attribute__ ((interrupt));

#endif /* PRT_IO_H_ */
