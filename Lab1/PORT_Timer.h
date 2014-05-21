/*
 * PORT_Timer.h
 *
 * Created: 19/05/2014 21:45:49
 *  Author: Karl Stiller
 */ 
#ifndef PORT_TIMER0_H_
#define PORT_TIMER0_H_

UINT8 PRT_Timer_bSet_Callback( void ( *pTimerFunc)( void ) );
UINT8 PRT_Timer_bInitializeTimer( UINT8 bVal );
UINT8 PRT_Timer_bGenerate_Interrupt( void );
UINT8 PRT_Timer_bTest_Callback( void );

/* vectors in AVR are hard coded to a function by name */
extern void ISR_TIMER0_COMPA (void) __attribute__ ((interrupt));
extern void ISR_TIMER0_COMPB (void) __attribute__ ((interrupt));
extern void ISR_TIMER0_OVF (void) __attribute__ ((interrupt));

#endif /* PORT_IO_H_ */
