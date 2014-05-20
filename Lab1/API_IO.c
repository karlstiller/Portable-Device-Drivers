/*
 * API_IO.c
 *
 * Created: 19/05/2014 22:03:27
 *  Author: Karl
 */
/* THIS FILE HAS NO PORTABLITY dependencies and should not have to    */
/* change for a different environment.                                */
#include "Port.h"
#include "PRT_IO.h"

UINT8 API_IO_bInitIO( void )
{
	return PRT_IO_bInitIO( );
}

UINT8 API_IO_bWriteLEDs( UINT8 bVal ){	return PRT_IO_bWriteLEDs( bVal );}UINT8 API_IO_bReadSwitches( void ){	return PRT_IO_bReadSwitches( );}