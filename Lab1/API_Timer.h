/*
 * API_Timer.h
 *
 * Created: 19/05/2014 22:44:48
 *  Author: Karl
 */ 


#ifndef API_TIMER_H_
#define API_TIMER_H_

UINT8 API_Timer_bInitializeTimer( void ( *pTimerFunc)( void ), UINT8 bVal );
UINT8 API_Timer_bGenerate_Interrupt( void );
UINT8 API_Timer_bTest_Callback( void );

#endif /* API_TIMER_H_ */