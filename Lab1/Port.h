/* Header for standard variable types*
 * and accessing cpu registers.      *
 *     Author: Karl Stiller          *
 *     Date: 22/04/2014              */
#ifndef PORT_H_
#define PORT_H_

#define READREG8( pReg ) ( *( volatile UINT8 * )( pReg ))
#define WRITEREG8( pReg, data ) ( *( volatile UINT8 * )( pReg )) = ( data )

#define READREG16( pReg ) ( *( volatile UINT16 * )( pReg ))
#define WRITEREG16( pReg, data ) ( *( volatile UINT16 * )( pReg )) = ( data )

#define UINT32 unsigned long
#define SINT32 signed long
#define UINT16 unsigned short
#define SINT16 signed short
#define UINT8 unsigned char
#define SINT8 signed char

/* interrupt is enabled at initialization */
/* sei – enables interrupts */
#define sei() __asm__ __volatile__ ("sei" ::)
/* cli – disables interrupts */
#define cli() __asm__ __volatile__ ("cli" ::)

#endif /* API_IO_H_ */

