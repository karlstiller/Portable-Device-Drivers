/*
 * SRL_API.c
 *
 * Created: 30/05/2014 18:32:43
 *  Author: karl.stiller
 */ 

#include "Port.h"
#include "SRL_API.h"
#include "SRL_PRT.h"
#include "SRL_API.h"


UINT8 SRL_bInitUart( UINT16 wBaudRate, UINT8 bNoDataBits, UINT8 bNoStop, SRL_ePARITY eParity )
{

	/* Parameter range checking */
	if (( wBaudRate < URT_MIN_BAUD ) ||
	( wBaudRate > URT_MAX_BAUD)) /* Limits for 1MHz clock */
	{
		return 1;
	}
	if (( bNoDataBits < URT_MIN_DATA_BITS ) ||
	( bNoDataBits > URT_MAX_DATA_BITS ))
	{
		return 1;
	}
	if (( bNoStop < URT_MIN_STOP_BITS ) ||
	( bNoStop > URT_MAX_STOP_BITS ))
	{
		return 1;
	}
	if (( bNoStop < URT_MIN_STOP_BITS ) ||
	( bNoStop > URT_MAX_STOP_BITS ))
	{
		return 1;
	}
	return SRL_PRT_bInitUart( wBaudRate, bNoDataBits, bNoStop, eParity );
}
