/*
 * API_IO.h
 *
 * Created: 19/05/2014 22:41:25
 * Author: Karl Stiller
 */ 


#ifndef API_IO_H_
#define API_IO_H_

UINT8 API_IO_bInitIO( void );
UINT8 API_IO_bWriteLEDs( UINT8 bVal );
UINT8 API_IO_bReadSwitches( void );

#endif /* API_IO_H_ */