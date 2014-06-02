/*
 * CRB_API.c
 *
 * Created: 30/05/2014 17:40:23
 *  Author: karl.stiller
 */ 
#include "Port.h"
#include "CRB_API.h"


void CRB_API_vInitCircularBuff( CRB_API_tsBuffCirc *psCircularBuff )
{
	memset( psCircularBuff->abBuffer, 0, sizeof( psCircularBuff->abBuffer));
	psCircularBuff->wMask = sizeof( psCircularBuff->abBuffer) - 1;
}

UINT8 CRB_API_bAddByteBuffer( UINT8 bByte, CRB_API_tsBuffCirc *psCircularBuff )
{
	/* Is there space in the buffer? */
	if ( ( ( psCircularBuff->wRemoval - 1 ) & psCircularBuff->wMask ) != psCircularBuff->wInsertion )
	{
		/* Add byte */
		psCircularBuff->abBuffer[psCircularBuff->wInsertion] = bByte;
		/* Increment pointer */
		psCircularBuff->wInsertion = (psCircularBuff->wInsertion + 1) & psCircularBuff->wMask;
		return 0;
	}
	return 1;
}

UINT8 CRB_API_bRemoveByteBuffer( UINT8 *pByte, CRB_API_tsBuffCirc *psCircularBuff )
{
	/* Is buffer empty? */
	if( psCircularBuff->wInsertion == psCircularBuff->wRemoval )
	{
		return 1;
	}
	/* Read byte */
	*pByte = psCircularBuff->abBuffer[psCircularBuff->wRemoval];
	/* Increment pointer */
	psCircularBuff->wRemoval = (psCircularBuff->wRemoval + 1) & psCircularBuff->wMask;
	return 0;
}

