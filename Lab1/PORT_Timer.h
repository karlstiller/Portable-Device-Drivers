/*
 * PORT_Timer.h
 *
 * Created: 19/05/2014 21:45:49
 *  Author: Karl
 */ 
#ifndef PRT_TIMER0_H_
#define PRT_TIMER0_H_

UINT8 PRT_Timer_bSet_Callback( void ( *pTimerFunc)( void ) );
UINT8 PRT_Timer_bInitializeTimer( UINT8 bVal );
UINT8 PRT_Timer_bGenerate_Interrupt( void );
UINT8 PRT_Timer_bTest_Callback( void );

/* vectors in AVR are hard coded to a function by name */
extern void __vector_20 (void) __attribute__ ((interrupt));
extern void __vector_21 (void) __attribute__ ((interrupt));
extern void __vector_22 (void) __attribute__ ((interrupt));
extern void __vector_23 (void) __attribute__ ((interrupt));
extern void __vector_24 (void) __attribute__ ((interrupt));

#endif /* PRT_IO_H_ */
