/*
 * CRB_API.h
 *
 * Created: 30/05/2014 17:28:58
 *  Author: karl.stiller
 */ 


#ifndef CRB_API_H_
#define CRB_API_H_

/* Structure to use with circular buffer */
typedef struct
{
	UINT8  abBuffer[4096];
	UINT16 wMask;
	UINT16 wInsertion;
	UINT16 wRemoval;
} CRB_API_tsBuffCirc;

void CRB_API_vInitCircularBuff( CRB_API_tsBuffCirc *psCircularBuff );
UINT8 CRB_API_bAddByteBuffer( UINT8 bByte, CRB_API_tsBuffCirc *psCircularBuff );
UINT8 CRB_API_bRemoveByteBuffer( UINT8 *pByte, CRB_API_tsBuffCirc *psCircularBuff );

#endif /* CRB_API_H_ */